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
struct tipc_sock {int /*<<< orphan*/  phdr; } ;

/* Variables and functions */
 int msg_importance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsk_importance(struct tipc_sock *tsk)
{
	return msg_importance(&tsk->phdr);
}