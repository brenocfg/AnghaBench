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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct iucv_path {struct sock* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_CONNECTED ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void iucv_callback_connack(struct iucv_path *path, u8 ipuser[16])
{
	struct sock *sk = path->private;

	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
}