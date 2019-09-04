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
struct spk_synth {scalar_t__ alive; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_tts; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (char const,int /*<<< orphan*/ ) ; 
 TYPE_1__ speakup_info ; 
 scalar_t__ spk_wait_for_xmitr (struct spk_synth*) ; 

__attribute__((used)) static int spk_serial_out(struct spk_synth *in_synth, const char ch)
{
	if (in_synth->alive && spk_wait_for_xmitr(in_synth)) {
		outb_p(ch, speakup_info.port_tts);
		return 1;
	}
	return 0;
}