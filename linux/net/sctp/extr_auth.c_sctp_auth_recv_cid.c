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
struct sctp_chunks_param {int dummy; } ;
struct TYPE_4__ {scalar_t__ auth_chunks; } ;
struct TYPE_3__ {int /*<<< orphan*/  auth_capable; } ;
struct sctp_association {TYPE_2__ c; TYPE_1__ peer; } ;
typedef  enum sctp_cid { ____Placeholder_sctp_cid } sctp_cid ;

/* Variables and functions */
 int __sctp_auth_cid (int,struct sctp_chunks_param*) ; 

int sctp_auth_recv_cid(enum sctp_cid chunk, const struct sctp_association *asoc)
{
	if (!asoc)
		return 0;

	if (!asoc->peer.auth_capable)
		return 0;

	return __sctp_auth_cid(chunk,
			      (struct sctp_chunks_param *)asoc->c.auth_chunks);
}