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
struct user_namespace {int /*<<< orphan*/  gid_map; } ;
struct seq_file {struct user_namespace* private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* m_start (struct seq_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *gid_m_start(struct seq_file *seq, loff_t *ppos)
{
	struct user_namespace *ns = seq->private;

	return m_start(seq, ppos, &ns->gid_map);
}