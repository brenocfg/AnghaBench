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
struct seq_file {int dummy; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_seq_printf_stats (struct seq_file*,void*) ; 

__attribute__((used)) static int wireless_dev_seq_show(struct seq_file *seq, void *v)
{
	might_sleep();

	if (v == SEQ_START_TOKEN)
		seq_printf(seq, "Inter-| sta-|   Quality        |   Discarded "
				"packets               | Missed | WE\n"
				" face | tus | link level noise |  nwid  "
				"crypt   frag  retry   misc | beacon | %d\n",
			   WIRELESS_EXT);
	else
		wireless_seq_printf_stats(seq, v);
	return 0;
}