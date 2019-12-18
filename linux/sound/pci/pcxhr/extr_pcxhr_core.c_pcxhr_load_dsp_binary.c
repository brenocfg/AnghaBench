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
struct pcxhr_mgr {int dummy; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_DSP_ISR ; 
 int /*<<< orphan*/  PCXHR_ISR_HI08_CHK ; 
 int /*<<< orphan*/  PCXHR_IT_DOWNLOAD_DSP ; 
 int /*<<< orphan*/  PCXHR_IT_RESET_BOARD_FUNC ; 
 int /*<<< orphan*/  PCXHR_TIMEOUT_DSP ; 
 int pcxhr_check_reg_bit (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int pcxhr_download_dsp (struct pcxhr_mgr*,struct firmware const*) ; 
 int pcxhr_send_it_dsp (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcxhr_load_dsp_binary(struct pcxhr_mgr *mgr, const struct firmware *dsp)
{
	int err;
	unsigned char dummy;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_BOARD_FUNC, 0);
	if (err)
		return err;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_DOWNLOAD_DSP, 0);
	if (err)
		return err;
	err = pcxhr_download_dsp(mgr, dsp);
	if (err)
		return err;
	/* wait for chk bit */
	return pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
				   PCXHR_ISR_HI08_CHK,
				   PCXHR_ISR_HI08_CHK,
				   PCXHR_TIMEOUT_DSP, &dummy);
}