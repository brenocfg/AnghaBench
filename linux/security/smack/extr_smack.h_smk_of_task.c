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
struct task_smack {struct smack_known* smk_task; } ;
struct smack_known {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct smack_known *smk_of_task(const struct task_smack *tsp)
{
	return tsp->smk_task;
}