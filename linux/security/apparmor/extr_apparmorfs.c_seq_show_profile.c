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
struct seq_file {struct aa_ns* private; } ;
struct aa_profile {int /*<<< orphan*/  label; } ;
struct aa_ns {int dummy; } ;

/* Variables and functions */
 int FLAG_SHOW_MODE ; 
 int FLAG_VIEW_SUBNS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  aa_label_seq_xprint (struct seq_file*,struct aa_ns*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int seq_show_profile(struct seq_file *f, void *p)
{
	struct aa_profile *profile = (struct aa_profile *)p;
	struct aa_ns *root = f->private;

	aa_label_seq_xprint(f, root, &profile->label,
			    FLAG_SHOW_MODE | FLAG_VIEW_SUBNS, GFP_KERNEL);
	seq_putc(f, '\n');

	return 0;
}