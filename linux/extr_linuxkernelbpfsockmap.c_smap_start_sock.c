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
struct sock {scalar_t__ sk_data_ready; int /*<<< orphan*/  sk_write_space; } ;
struct smap_psock {scalar_t__ save_data_ready; int strp_enabled; int /*<<< orphan*/  save_write_space; } ;

/* Variables and functions */
 scalar_t__ smap_data_ready ; 
 int /*<<< orphan*/  smap_write_space ; 

__attribute__((used)) static void smap_start_sock(struct smap_psock *psock, struct sock *sk)
{
	if (sk->sk_data_ready == smap_data_ready)
		return;
	psock->save_data_ready = sk->sk_data_ready;
	psock->save_write_space = sk->sk_write_space;
	sk->sk_data_ready = smap_data_ready;
	sk->sk_write_space = smap_write_space;
	psock->strp_enabled = true;
}