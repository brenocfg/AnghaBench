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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_sock {int /*<<< orphan*/  phdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int TIPC_CRITICAL_IMPORTANCE ; 
 int /*<<< orphan*/  msg_set_importance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsk_set_importance(struct tipc_sock *tsk, int imp)
{
	if (imp > TIPC_CRITICAL_IMPORTANCE)
		return -EINVAL;
	msg_set_importance(&tsk->phdr, (u32)imp);
	return 0;
}