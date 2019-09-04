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
struct user_namespace {struct user_namespace* parent; } ;
struct uid_gid_extent {int /*<<< orphan*/  count; int /*<<< orphan*/  first; int /*<<< orphan*/  lower_first; } ;
struct seq_file {struct user_namespace* private; } ;
typedef  int /*<<< orphan*/  projid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KPROJIDT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kprojid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct user_namespace* seq_user_ns (struct seq_file*) ; 

__attribute__((used)) static int projid_m_show(struct seq_file *seq, void *v)
{
	struct user_namespace *ns = seq->private;
	struct uid_gid_extent *extent = v;
	struct user_namespace *lower_ns;
	projid_t lower;

	lower_ns = seq_user_ns(seq);
	if ((lower_ns == ns) && lower_ns->parent)
		lower_ns = lower_ns->parent;

	lower = from_kprojid(lower_ns, KPROJIDT_INIT(extent->lower_first));

	seq_printf(seq, "%10u %10u %10u\n",
		extent->first,
		lower,
		extent->count);

	return 0;
}