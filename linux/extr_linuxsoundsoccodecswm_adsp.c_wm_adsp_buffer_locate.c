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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ u32 ;
struct wm_coeff_ctl {int dummy; } ;
struct wm_adsp_compr_buf {int /*<<< orphan*/  host_buf_ptr; struct wm_adsp* dsp; } ;
struct wm_adsp {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 int regmap_raw_read (int /*<<< orphan*/ ,unsigned int,scalar_t__*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 struct wm_coeff_ctl* wm_adsp_find_host_buffer_ctrl (struct wm_adsp_compr_buf*) ; 
 int wm_adsp_legacy_host_buf_addr (struct wm_adsp_compr_buf*) ; 
 int wm_coeff_base_reg (struct wm_coeff_ctl*,unsigned int*) ; 

__attribute__((used)) static int wm_adsp_buffer_locate(struct wm_adsp_compr_buf *buf)
{
	struct wm_adsp *dsp = buf->dsp;
	struct wm_coeff_ctl *ctl;
	unsigned int reg;
	u32 val;
	int i, ret;

	ctl = wm_adsp_find_host_buffer_ctrl(buf);
	if (!ctl)
		return wm_adsp_legacy_host_buf_addr(buf);

	ret = wm_coeff_base_reg(ctl, &reg);
	if (ret)
		return ret;

	for (i = 0; i < 5; ++i) {
		ret = regmap_raw_read(dsp->regmap, reg, &val, sizeof(val));
		if (ret < 0)
			return ret;

		if (val)
			break;

		usleep_range(1000, 2000);
	}

	if (!val)
		return -EIO;

	buf->host_buf_ptr = be32_to_cpu(val);
	adsp_dbg(dsp, "host_buf_ptr=%x\n", buf->host_buf_ptr);

	return 0;
}