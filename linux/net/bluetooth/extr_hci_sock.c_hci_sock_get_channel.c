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
struct sock {int dummy; } ;
struct TYPE_2__ {unsigned short channel; } ;

/* Variables and functions */
 TYPE_1__* hci_pi (struct sock*) ; 

unsigned short hci_sock_get_channel(struct sock *sk)
{
	return hci_pi(sk)->channel;
}