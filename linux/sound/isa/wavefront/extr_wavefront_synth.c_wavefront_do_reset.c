#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int freemem; scalar_t__ interrupts_are_midi; int /*<<< orphan*/  control_port; scalar_t__ debug; int /*<<< orphan*/  irq_ok; int /*<<< orphan*/  data_port; scalar_t__ israw; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  WFC_NOOP ; 
 int /*<<< orphan*/  WFC_SET_NVOICES ; 
 int /*<<< orphan*/  ospath ; 
 int osrun_time ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printk (char*,...) ; 
 scalar_t__ snd_wavefront_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wavefront_download_firmware (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int wavefront_freemem (TYPE_1__*) ; 
 scalar_t__ wavefront_read (TYPE_1__*) ; 
 scalar_t__ wavefront_reset_to_cleanliness (TYPE_1__*) ; 
 int /*<<< orphan*/  wavefront_should_cause_interrupt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wavefront_write (TYPE_1__*,int) ; 

__attribute__((used)) static int
wavefront_do_reset (snd_wavefront_t *dev)

{
	char voices[1];

	if (wavefront_reset_to_cleanliness (dev)) {
		snd_printk ("hw reset failed.\n");
		goto gone_bad;
	}

	if (dev->israw) {
		if (wavefront_download_firmware (dev, ospath)) {
			goto gone_bad;
		}

		dev->israw = 0;

		/* Wait for the OS to get running. The protocol for
		   this is non-obvious, and was determined by
		   using port-IO tracing in DOSemu and some
		   experimentation here.
		   
		   Rather than using timed waits, use interrupts creatively.
		*/

		wavefront_should_cause_interrupt (dev, WFC_NOOP,
						  dev->data_port,
						  (osrun_time*HZ));

		if (!dev->irq_ok) {
			snd_printk ("no post-OS interrupt.\n");
			goto gone_bad;
		}
		
		/* Now, do it again ! */
		
		wavefront_should_cause_interrupt (dev, WFC_NOOP,
						  dev->data_port, (10*HZ));
		
		if (!dev->irq_ok) {
			snd_printk ("no post-OS interrupt(2).\n");
			goto gone_bad;
		}

		/* OK, no (RX/TX) interrupts any more, but leave mute
		   in effect. 
		*/
		
		outb (0x80|0x40, dev->control_port); 
	}

	/* SETUPSND.EXE asks for sample memory config here, but since i
	   have no idea how to interpret the result, we'll forget
	   about it.
	*/
	
	if ((dev->freemem = wavefront_freemem (dev)) < 0) {
		goto gone_bad;
	}
		
	snd_printk ("available DRAM %dk\n", dev->freemem / 1024);

	if (wavefront_write (dev, 0xf0) ||
	    wavefront_write (dev, 1) ||
	    (wavefront_read (dev) < 0)) {
		dev->debug = 0;
		snd_printk ("MPU emulation mode not set.\n");
		goto gone_bad;
	}

	voices[0] = 32;

	if (snd_wavefront_cmd (dev, WFC_SET_NVOICES, NULL, voices)) {
		snd_printk ("cannot set number of voices to 32.\n");
		goto gone_bad;
	}


	return 0;

 gone_bad:
	/* reset that sucker so that it doesn't bother us. */

	outb (0x0, dev->control_port);
	dev->interrupts_are_midi = 0;
	return 1;
}