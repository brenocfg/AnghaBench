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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCP_CA_Open ; 
 int /*<<< orphan*/  vegas_disable (struct sock*) ; 
 int /*<<< orphan*/  vegas_enable (struct sock*) ; 

void tcp_vegas_state(struct sock *sk, u8 ca_state)
{
	if (ca_state == TCP_CA_Open)
		vegas_enable(sk);
	else
		vegas_disable(sk);
}