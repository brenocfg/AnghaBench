#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct gb_host_device {int dummy; } ;
struct es2_ap_dev {TYPE_1__* usb_dev; } ;
struct device {int dummy; } ;
struct arpc_cport_flush_req {int /*<<< orphan*/  cport_id; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPC_TYPE_CPORT_FLUSH ; 
 int /*<<< orphan*/  ES2_ARPC_CPORT_TIMEOUT ; 
 int arpc_sync (struct es2_ap_dev*,int /*<<< orphan*/ ,struct arpc_cport_flush_req*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct es2_ap_dev* hd_to_es2 (struct gb_host_device*) ; 

__attribute__((used)) static int es2_cport_flush(struct gb_host_device *hd, u16 cport_id)
{
	struct es2_ap_dev *es2 = hd_to_es2(hd);
	struct device *dev = &es2->usb_dev->dev;
	struct arpc_cport_flush_req req;
	int ret;

	req.cport_id = cpu_to_le16(cport_id);
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_FLUSH, &req, sizeof(req),
			NULL, ES2_ARPC_CPORT_TIMEOUT);
	if (ret) {
		dev_err(dev, "failed to flush cport %u: %d\n", cport_id, ret);
		return ret;
	}

	return 0;
}