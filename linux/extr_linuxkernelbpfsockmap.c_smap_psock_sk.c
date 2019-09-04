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
struct sock {int dummy; } ;
struct smap_psock {int dummy; } ;

/* Variables and functions */
 struct smap_psock* rcu_dereference_sk_user_data (struct sock const*) ; 

__attribute__((used)) static inline struct smap_psock *smap_psock_sk(const struct sock *sk)
{
	return rcu_dereference_sk_user_data(sk);
}