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
struct tty_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ alive; int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speakup_start_ttys () ; 
 TYPE_1__* spk_ttyio_synth ; 

__attribute__((used)) static int check_tty(struct tty_struct *tty)
{
	if (!tty) {
		pr_warn("%s: I/O error, deactivating speakup\n",
			spk_ttyio_synth->long_name);
		/* No synth any more, so nobody will restart TTYs, and we thus
		 * need to do it ourselves.  Now that there is no synth we can
		 * let application flood anyway
		 */
		spk_ttyio_synth->alive = 0;
		speakup_start_ttys();
		return 1;
	}

	return 0;
}