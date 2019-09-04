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
struct spk_synth {int /*<<< orphan*/  long_name; TYPE_1__* io_ops; int /*<<< orphan*/  (* synth_immediate ) (struct spk_synth*,char*) ;} ;
struct TYPE_2__ {char (* synth_in ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct spk_synth*,char*) ; 
 char stub2 () ; 
 char stub3 () ; 

__attribute__((used)) static void synth_version(struct spk_synth *synth)
{
	unsigned char test = 0;
	char synth_id[40] = "";

	synth->synth_immediate(synth, "\x05[Q]");
	synth_id[test] = synth->io_ops->synth_in();
	if (synth_id[test] == 'A') {
		do {
			/* read version string from synth */
			synth_id[++test] = synth->io_ops->synth_in();
		} while (synth_id[test] != '\n' && test < 32);
		synth_id[++test] = 0x00;
	}
	if (synth_id[0] == 'A')
		pr_info("%s version: %s", synth->long_name, synth_id);
}