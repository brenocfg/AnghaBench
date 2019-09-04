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
typedef  char u_char ;
struct spk_synth {int dummy; } ;

/* Variables and functions */
 char PROCSPEECH ; 
 char const* oops () ; 
 int /*<<< orphan*/  outb_p (char,int /*<<< orphan*/ ) ; 
 scalar_t__ synth_full () ; 
 int /*<<< orphan*/  synth_port ; 
 scalar_t__ synth_writable () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static const char *synth_immediate(struct spk_synth *synth, const char *buf)
{
	u_char ch;
	int timeout;

	while ((ch = *buf)) {
		if (ch == '\n')
			ch = PROCSPEECH;
		if (synth_full())
			return buf;
		timeout = 1000;
		while (synth_writable())
			if (--timeout <= 0)
				return oops();
		outb_p(ch, synth_port);
		udelay(70);
		buf++;
	}
	return NULL;
}