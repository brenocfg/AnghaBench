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
struct sctp_sock {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_IPV4_ADDRESS ; 

__attribute__((used)) static int sctp_inet_supported_addrs(const struct sctp_sock *opt,
				     __be16 *types)
{
	types[0] = SCTP_PARAM_IPV4_ADDRESS;
	return 1;
}