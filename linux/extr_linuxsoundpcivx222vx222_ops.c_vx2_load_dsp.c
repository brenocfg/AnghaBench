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
struct vx_core {int dummy; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_vx_dsp_boot (struct vx_core*,struct firmware const*) ; 
 int snd_vx_dsp_load (struct vx_core*,struct firmware const*) ; 
 int vx2_load_xilinx_binary (struct vx_core*,struct firmware const*) ; 
 int vx2_test_xilinx (struct vx_core*) ; 

__attribute__((used)) static int vx2_load_dsp(struct vx_core *vx, int index, const struct firmware *dsp)
{
	int err;

	switch (index) {
	case 1:
		/* xilinx image */
		if ((err = vx2_load_xilinx_binary(vx, dsp)) < 0)
			return err;
		if ((err = vx2_test_xilinx(vx)) < 0)
			return err;
		return 0;
	case 2:
		/* DSP boot */
		return snd_vx_dsp_boot(vx, dsp);
	case 3:
		/* DSP image */
		return snd_vx_dsp_load(vx, dsp);
	default:
		snd_BUG();
		return -EINVAL;
	}
}