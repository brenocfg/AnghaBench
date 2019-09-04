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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int sctp_inet_send_verify(struct sctp_sock *opt, union sctp_addr *addr)
{
	return 1;
}