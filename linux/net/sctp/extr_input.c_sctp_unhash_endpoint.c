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
struct sctp_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sctp_unhash_endpoint (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

void sctp_unhash_endpoint(struct sctp_endpoint *ep)
{
	local_bh_disable();
	__sctp_unhash_endpoint(ep);
	local_bh_enable();
}