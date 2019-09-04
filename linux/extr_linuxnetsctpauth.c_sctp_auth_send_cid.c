#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  peer_chunks; int /*<<< orphan*/  auth_capable; } ;
struct sctp_association {TYPE_2__ peer; TYPE_1__* ep; } ;
typedef  enum sctp_cid { ____Placeholder_sctp_cid } sctp_cid ;
struct TYPE_3__ {int /*<<< orphan*/  auth_enable; } ;

/* Variables and functions */
 int __sctp_auth_cid (int,int /*<<< orphan*/ ) ; 

int sctp_auth_send_cid(enum sctp_cid chunk, const struct sctp_association *asoc)
{
	if (!asoc)
		return 0;

	if (!asoc->ep->auth_enable || !asoc->peer.auth_capable)
		return 0;

	return __sctp_auth_cid(chunk, asoc->peer.peer_chunks);
}