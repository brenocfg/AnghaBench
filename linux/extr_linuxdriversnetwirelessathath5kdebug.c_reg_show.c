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
struct seq_file {struct ath5k_hw* private; } ;
struct reg {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_show(struct seq_file *seq, void *p)
{
	struct ath5k_hw *ah = seq->private;
	struct reg *r = p;
	seq_printf(seq, "%-25s0x%08x\n", r->name,
		ath5k_hw_reg_read(ah, r->addr));
	return 0;
}