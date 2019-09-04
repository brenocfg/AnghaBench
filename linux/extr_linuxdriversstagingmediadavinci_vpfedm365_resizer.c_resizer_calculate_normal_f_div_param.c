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
struct TYPE_4__ {TYPE_1__* pass; int /*<<< orphan*/  num_passes; } ;
struct resizer_scale_param {TYPE_2__ f_div; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int o_hsz; unsigned int i_hps; unsigned int h_phs; int src_hps; int src_hsz; } ;

/* Variables and functions */
 int CEIL (unsigned int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_PASSES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int
resizer_calculate_normal_f_div_param(struct device *dev, int input_width,
		int output_width, struct resizer_scale_param *param)
{
	/* rsz = R, input_width = H, output width = h in the equation */
	unsigned int val1;
	unsigned int rsz;
	unsigned int val;
	unsigned int h1;
	unsigned int h2;
	unsigned int o;

	if (output_width > input_width) {
		dev_err(dev, "frame div mode is used for scale down only\n");
		return -EINVAL;
	}

	rsz = (input_width << 8) / output_width;
	val = rsz << 1;
	val = ((input_width << 8) / val) + 1;
	o = 14;
	if (!(val % 2)) {
		h1 = val;
	} else {
		val = input_width << 7;
		val -= rsz >> 1;
		val /= rsz << 1;
		val <<= 1;
		val += 2;
		o += ((CEIL(rsz, 1024)) << 1);
		h1 = val;
	}
	h2 = output_width - h1;
	/* phi */
	val = (h1 * rsz) - (((input_width >> 1) - o) << 8);
	/* skip */
	val1 = ((val - 1024) >> 9) << 1;
	param->f_div.num_passes = MAX_PASSES;
	param->f_div.pass[0].o_hsz = h1 - 1;
	param->f_div.pass[0].i_hps = 0;
	param->f_div.pass[0].h_phs = 0;
	param->f_div.pass[0].src_hps = 0;
	param->f_div.pass[0].src_hsz = (input_width >> 2) + o;
	param->f_div.pass[1].o_hsz = h2 - 1;
	param->f_div.pass[1].i_hps = val1;
	param->f_div.pass[1].h_phs = val - (val1 << 8);
	param->f_div.pass[1].src_hps = (input_width >> 2) - o;
	param->f_div.pass[1].src_hsz = (input_width >> 2) + o;

	return 0;
}