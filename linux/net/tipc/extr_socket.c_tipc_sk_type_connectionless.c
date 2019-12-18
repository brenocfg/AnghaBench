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
struct sock {scalar_t__ sk_type; } ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RDM ; 

__attribute__((used)) static bool tipc_sk_type_connectionless(struct sock *sk)
{
	return sk->sk_type == SOCK_RDM || sk->sk_type == SOCK_DGRAM;
}