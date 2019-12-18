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
struct mount {int /*<<< orphan*/  mnt_writers; TYPE_1__* mnt_pcp; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mnt_inc_writers(struct mount *mnt)
{
#ifdef CONFIG_SMP
	this_cpu_inc(mnt->mnt_pcp->mnt_writers);
#else
	mnt->mnt_writers++;
#endif
}