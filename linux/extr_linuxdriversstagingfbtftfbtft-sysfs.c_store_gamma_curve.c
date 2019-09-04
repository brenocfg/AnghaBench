#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tmp_curves ;
struct TYPE_4__ {int num_curves; int num_values; int /*<<< orphan*/  lock; int /*<<< orphan*/  curves; } ;
struct TYPE_3__ {int (* set_gamma ) (struct fbtft_par*,int /*<<< orphan*/ *) ;} ;
struct fbtft_par {TYPE_2__ gamma; TYPE_1__ fbtftops; } ;
struct fb_info {struct fbtft_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int FBTFT_GAMMA_MAX_VALUES_TOTAL ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int fbtft_gamma_parse_str (struct fbtft_par*,int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct fbtft_par*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_gamma_curve(struct device *device,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fbtft_par *par = fb_info->par;
	u32 tmp_curves[FBTFT_GAMMA_MAX_VALUES_TOTAL];
	int ret;

	ret = fbtft_gamma_parse_str(par, tmp_curves, buf, count);
	if (ret)
		return ret;

	ret = par->fbtftops.set_gamma(par, tmp_curves);
	if (ret)
		return ret;

	mutex_lock(&par->gamma.lock);
	memcpy(par->gamma.curves, tmp_curves,
	       par->gamma.num_curves * par->gamma.num_values *
	       sizeof(tmp_curves[0]));
	mutex_unlock(&par->gamma.lock);

	return count;
}