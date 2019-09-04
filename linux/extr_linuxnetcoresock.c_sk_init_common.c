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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sock {size_t sk_family; int /*<<< orphan*/  sk_callback_lock; TYPE_1__ sk_error_queue; TYPE_1__ sk_write_queue; TYPE_1__ sk_receive_queue; } ;

/* Variables and functions */
 scalar_t__ af_callback_keys ; 
 scalar_t__ af_elock_keys ; 
 int /*<<< orphan*/ * af_family_clock_key_strings ; 
 int /*<<< orphan*/ * af_family_elock_key_strings ; 
 int /*<<< orphan*/ * af_family_rlock_key_strings ; 
 int /*<<< orphan*/ * af_family_wlock_key_strings ; 
 scalar_t__ af_rlock_keys ; 
 scalar_t__ af_wlock_keys ; 
 int /*<<< orphan*/  lockdep_set_class_and_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (TYPE_1__*) ; 

__attribute__((used)) static void sk_init_common(struct sock *sk)
{
	skb_queue_head_init(&sk->sk_receive_queue);
	skb_queue_head_init(&sk->sk_write_queue);
	skb_queue_head_init(&sk->sk_error_queue);

	rwlock_init(&sk->sk_callback_lock);
	lockdep_set_class_and_name(&sk->sk_receive_queue.lock,
			af_rlock_keys + sk->sk_family,
			af_family_rlock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_write_queue.lock,
			af_wlock_keys + sk->sk_family,
			af_family_wlock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_error_queue.lock,
			af_elock_keys + sk->sk_family,
			af_family_elock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_callback_lock,
			af_callback_keys + sk->sk_family,
			af_family_clock_key_strings[sk->sk_family]);
}