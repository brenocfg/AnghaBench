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
struct sock {int sk_family; } ;

/* Variables and functions */
#define  AF_UNIX 129 
#define  AF_UNSPEC 128 

__attribute__((used)) static bool sock_needs_netstamp(const struct sock *sk)
{
	switch (sk->sk_family) {
	case AF_UNSPEC:
	case AF_UNIX:
		return false;
	default:
		return true;
	}
}