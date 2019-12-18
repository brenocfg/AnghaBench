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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_DSP_BAR ; 
 int SHIM_BYT_CSR_RST ; 
 int SHIM_BYT_CSR_STALL ; 
 int SHIM_BYT_CSR_VECTOR_SEL ; 
 int /*<<< orphan*/  SHIM_CSR ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int byt_reset(struct snd_sof_dev *sdev)
{
	/* put DSP into reset, set reset vector and stall */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL |
				  SHIM_BYT_CSR_STALL,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL |
				  SHIM_BYT_CSR_STALL);

	usleep_range(10, 15);

	/* take DSP out of reset and keep stalled for FW loading */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_RST, 0);

	return 0;
}