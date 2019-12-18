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
 int /*<<< orphan*/  msg_prevnode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 tsk_own_node(struct tipc_sock *tsk)
{
	return msg_prevnode(&tsk->phdr);
}