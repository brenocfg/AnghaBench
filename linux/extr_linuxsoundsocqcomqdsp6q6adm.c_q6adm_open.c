#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct q6copp {int copp_idx; int topology; int mode; int rate; int channels; int app_type; int /*<<< orphan*/  refcount; int /*<<< orphan*/  bit_width; int /*<<< orphan*/  node; } ;
struct q6adm {int /*<<< orphan*/  copps_list_lock; int /*<<< orphan*/  copps_list; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 struct q6copp* ERR_CAST (struct q6copp*) ; 
 struct q6copp* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct q6copp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct q6adm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct q6copp* q6adm_alloc_copp (struct q6adm*,int) ; 
 int q6adm_device_open (struct q6adm*,struct q6copp*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 struct q6copp* q6adm_find_matching_copp (struct q6adm*,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  q6adm_free_copp ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct q6copp *q6adm_open(struct device *dev, int port_id, int path, int rate,
	       int channel_mode, int topology, int perf_mode,
	       uint16_t bit_width, int app_type, int acdb_id)
{
	struct q6adm *adm = dev_get_drvdata(dev->parent);
	struct q6copp *copp;
	unsigned long flags;
	int ret = 0;

	if (port_id < 0) {
		dev_err(dev, "Invalid port_id 0x%x\n", port_id);
		return ERR_PTR(-EINVAL);
	}

	copp = q6adm_find_matching_copp(adm, port_id, topology, perf_mode,
				      rate, channel_mode, bit_width, app_type);
	if (copp) {
		dev_err(dev, "Found Matching Copp 0x%x\n", copp->copp_idx);
		return copp;
	}

	spin_lock_irqsave(&adm->copps_list_lock, flags);
	copp = q6adm_alloc_copp(adm, port_id);
	if (IS_ERR_OR_NULL(copp)) {
		spin_unlock_irqrestore(&adm->copps_list_lock, flags);
		return ERR_CAST(copp);
	}

	list_add_tail(&copp->node, &adm->copps_list);
	spin_unlock_irqrestore(&adm->copps_list_lock, flags);

	kref_init(&copp->refcount);
	copp->topology = topology;
	copp->mode = perf_mode;
	copp->rate = rate;
	copp->channels = channel_mode;
	copp->bit_width = bit_width;
	copp->app_type = app_type;


	ret = q6adm_device_open(adm, copp, port_id, path, topology,
				channel_mode, bit_width, rate);
	if (ret < 0) {
		kref_put(&copp->refcount, q6adm_free_copp);
		return ERR_PTR(ret);
	}

	return copp;
}