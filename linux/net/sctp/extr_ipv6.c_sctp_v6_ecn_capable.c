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
struct TYPE_2__ {int /*<<< orphan*/  tclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_ECT_0 ; 
 TYPE_1__* inet6_sk (struct sock*) ; 

__attribute__((used)) static void sctp_v6_ecn_capable(struct sock *sk)
{
	inet6_sk(sk)->tclass |= INET_ECN_ECT_0;
}