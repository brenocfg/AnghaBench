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
struct snd_aw2_saa7146 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_callback_param; int /*<<< orphan*/  (* p_it_callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  p_callback_param; int /*<<< orphan*/  (* p_it_callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int A1_in ; 
 unsigned int A1_out ; 
 unsigned int A2_out ; 
 int /*<<< orphan*/  IICSTA ; 
 unsigned int IIC_E ; 
 unsigned int IIC_S ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR ; 
 unsigned int READREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEREG (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* arr_substream_it_capture_cb ; 
 TYPE_1__* arr_substream_it_playback_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

irqreturn_t snd_aw2_saa7146_interrupt(int irq, void *dev_id)
{
	unsigned int isr;
	unsigned int iicsta;
	struct snd_aw2_saa7146 *chip = dev_id;

	isr = READREG(ISR);
	if (!isr)
		return IRQ_NONE;

	WRITEREG(isr, ISR);

	if (isr & (IIC_S | IIC_E)) {
		iicsta = READREG(IICSTA);
		WRITEREG(0x100, IICSTA);
	}

	if (isr & A1_out) {
		if (arr_substream_it_playback_cb[1].p_it_callback != NULL) {
			arr_substream_it_playback_cb[1].
			    p_it_callback(arr_substream_it_playback_cb[1].
					  p_callback_param);
		}
	}
	if (isr & A2_out) {
		if (arr_substream_it_playback_cb[0].p_it_callback != NULL) {
			arr_substream_it_playback_cb[0].
			    p_it_callback(arr_substream_it_playback_cb[0].
					  p_callback_param);
		}

	}
	if (isr & A1_in) {
		if (arr_substream_it_capture_cb[0].p_it_callback != NULL) {
			arr_substream_it_capture_cb[0].
			    p_it_callback(arr_substream_it_capture_cb[0].
					  p_callback_param);
		}
	}
	return IRQ_HANDLED;
}