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
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_unlock_object (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline void ipc_unlock(struct kern_ipc_perm *perm)
{
	ipc_unlock_object(perm);
	rcu_read_unlock();
}