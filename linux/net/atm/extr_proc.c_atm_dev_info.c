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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aal5; int /*<<< orphan*/  aal0; } ;
struct atm_dev {int /*<<< orphan*/  refcnt; TYPE_1__ stats; int /*<<< orphan*/ * esi; int /*<<< orphan*/  type; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ESI_LEN ; 
 int /*<<< orphan*/  add_stats (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void atm_dev_info(struct seq_file *seq, const struct atm_dev *dev)
{
	int i;

	seq_printf(seq, "%3d %-8s", dev->number, dev->type);
	for (i = 0; i < ESI_LEN; i++)
		seq_printf(seq, "%02x", dev->esi[i]);
	seq_puts(seq, "  ");
	add_stats(seq, "0", &dev->stats.aal0);
	seq_puts(seq, "  ");
	add_stats(seq, "5", &dev->stats.aal5);
	seq_printf(seq, "\t[%d]", refcount_read(&dev->refcnt));
	seq_putc(seq, '\n');
}