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
struct tipc_sock {scalar_t__ snt_unacked; scalar_t__ snd_win; } ;

/* Variables and functions */

__attribute__((used)) static bool tsk_conn_cong(struct tipc_sock *tsk)
{
	return tsk->snt_unacked > tsk->snd_win;
}