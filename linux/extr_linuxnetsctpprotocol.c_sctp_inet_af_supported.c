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
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 

__attribute__((used)) static int sctp_inet_af_supported(sa_family_t family, struct sctp_sock *sp)
{
	/* PF_INET only supports AF_INET addresses. */
	return AF_INET == family;
}