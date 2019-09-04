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
typedef  int u8 ;
struct sock {int sk_family; } ;

/* Variables and functions */
#define  PF_INET 130 
#define  PF_INET6 129 
#define  PF_UNIX 128 
 scalar_t__ tomoyo_kernel_service () ; 

__attribute__((used)) static u8 tomoyo_sock_family(struct sock *sk)
{
	u8 family;

	if (tomoyo_kernel_service())
		return 0;
	family = sk->sk_family;
	switch (family) {
	case PF_INET:
	case PF_INET6:
	case PF_UNIX:
		return family;
	default:
		return 0;
	}
}