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
struct seq_file {struct aa_proxy* private; } ;
struct aa_proxy {int /*<<< orphan*/  label; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct aa_profile {TYPE_1__ base; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* aa_get_label_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 struct aa_profile* labels_profile (struct aa_label*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_profile_name_show(struct seq_file *seq, void *v)
{
	struct aa_proxy *proxy = seq->private;
	struct aa_label *label = aa_get_label_rcu(&proxy->label);
	struct aa_profile *profile = labels_profile(label);
	seq_printf(seq, "%s\n", profile->base.name);
	aa_put_label(label);

	return 0;
}