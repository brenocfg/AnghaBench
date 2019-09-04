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
struct sock {int /*<<< orphan*/ * sk_write_space; int /*<<< orphan*/ * sk_data_ready; } ;
struct smap_psock {int strp_enabled; int /*<<< orphan*/  strp; int /*<<< orphan*/ * save_write_space; int /*<<< orphan*/ * save_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  strp_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smap_stop_sock(struct smap_psock *psock, struct sock *sk)
{
	if (!psock->strp_enabled)
		return;
	sk->sk_data_ready = psock->save_data_ready;
	sk->sk_write_space = psock->save_write_space;
	psock->save_data_ready = NULL;
	psock->save_write_space = NULL;
	strp_stop(&psock->strp);
	psock->strp_enabled = false;
}