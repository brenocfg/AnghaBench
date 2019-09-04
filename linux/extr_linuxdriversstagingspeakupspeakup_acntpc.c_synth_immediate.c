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
typedef  char u_char ;
struct spk_synth {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_tts; } ;

/* Variables and functions */
 char PROCSPEECH ; 
 int SPK_XMITR_TIMEOUT ; 
 int /*<<< orphan*/  outb_p (char,int /*<<< orphan*/ ) ; 
 TYPE_1__ speakup_info ; 
 scalar_t__ synth_full () ; 
 scalar_t__ synth_writable () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static const char *synth_immediate(struct spk_synth *synth, const char *buf)
{
	u_char ch;

	while ((ch = *buf)) {
		int timeout = SPK_XMITR_TIMEOUT;

		if (ch == '\n')
			ch = PROCSPEECH;
		if (synth_full())
			return buf;
		while (synth_writable()) {
			if (!--timeout)
				return buf;
			udelay(1);
		}
		outb_p(ch, speakup_info.port_tts);
		buf++;
	}
	return NULL;
}