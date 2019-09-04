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
struct resizer_scale_param {unsigned int h_dscale_ave_sz; TYPE_2__ f_div; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int o_hsz; int i_hps; unsigned int h_phs; unsigned int src_hps; unsigned int src_hsz; } ;

/* Variables and functions */
 int CEIL (unsigned int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_PASSES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int
resizer_calculate_down_scale_f_div_param(struct device *dev,
					 int input_width, int output_width,
					 struct resizer_scale_param *param)
{
	/* rsz = R, input_width = H, output width = h in the equation */
	unsigned int two_power;
	unsigned int upper_h1;
	unsigned int upper_h2;
	unsigned int val1;
	unsigned int val;
	unsigned int rsz;
	unsigned int h1;
	unsigned int h2;
	unsigned int o;
	unsigned int n;

	upper_h1 = input_width >> 1;
	n = param->h_dscale_ave_sz;
	/* 2 ^ (scale+1) */
	two_power = 1 << (n + 1);
	upper_h1 = (upper_h1 >> (n + 1)) << (n + 1);
	upper_h2 = input_width - upper_h1;
	if (upper_h2 % two_power) {
		dev_err(dev, "frame halves to be a multiple of 2 power n+1\n");
		return -EINVAL;
	}
	two_power = 1 << n;
	rsz = (input_width << 8) / output_width;
	val = rsz * two_power;
	val = ((upper_h1 << 8) / val) + 1;
	if (!(val % 2)) {
		h1 = val;
	} else {
		val = upper_h1 << 8;
		val >>= n + 1;
		val -= rsz >> 1;
		val /= rsz << 1;
		val <<= 1;
		val += 2;
		h1 = val;
	}
	o = 10 + (two_power << 2);
	if (((input_width << 7) / rsz) % 2)
		o += (((CEIL(rsz, 1024)) << 1) << n);
	h2 = output_width - h1;
	/* phi */
	val = (h1 * rsz) - (((upper_h1 - (o - 10)) / two_power) << 8);
	/* skip */
	val1 = ((val - 1024) >> 9) << 1;
	param->f_div.num_passes = MAX_PASSES;
	param->f_div.pass[0].o_hsz = h1 - 1;
	param->f_div.pass[0].i_hps = 0;
	param->f_div.pass[0].h_phs = 0;
	param->f_div.pass[0].src_hps = 0;
	param->f_div.pass[0].src_hsz = upper_h1 + o;
	param->f_div.pass[1].o_hsz = h2 - 1;
	param->f_div.pass[1].i_hps = 10 + (val1 * two_power);
	param->f_div.pass[1].h_phs = val - (val1 << 8);
	param->f_div.pass[1].src_hps = upper_h1 - o;
	param->f_div.pass[1].src_hsz = upper_h2 + o;

	return 0;
}