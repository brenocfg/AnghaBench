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
struct task_smack {int /*<<< orphan*/  smk_relabel; } ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_cred () ; 
 struct task_smack* smack_cred (int /*<<< orphan*/ ) ; 
 void* smk_seq_start (struct seq_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *relabel_self_seq_start(struct seq_file *s, loff_t *pos)
{
	struct task_smack *tsp = smack_cred(current_cred());

	return smk_seq_start(s, pos, &tsp->smk_relabel);
}