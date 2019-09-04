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
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {int /*<<< orphan*/  transport; scalar_t__ auth_chunk; struct sctp_chunkhdr* chunk_hdr; int /*<<< orphan*/  sctp_hdr; int /*<<< orphan*/  asoc; scalar_t__ skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  auth_capable; } ;
struct sctp_association {TYPE_1__ peer; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth_enable; } ;
struct net {TYPE_2__ sctp; } ;

/* Variables and functions */
 scalar_t__ SCTP_IERROR_NO_ERROR ; 
 scalar_t__ sctp_sf_authenticate (struct sctp_association const*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  skb_pull (scalar_t__,int) ; 
 scalar_t__ skb_push (scalar_t__,int) ; 

__attribute__((used)) static bool sctp_auth_chunk_verify(struct net *net, struct sctp_chunk *chunk,
				   const struct sctp_association *asoc)
{
	struct sctp_chunk auth;

	if (!chunk->auth_chunk)
		return true;

	/* SCTP-AUTH:  auth_chunk pointer is only set when the cookie-echo
	 * is supposed to be authenticated and we have to do delayed
	 * authentication.  We've just recreated the association using
	 * the information in the cookie and now it's much easier to
	 * do the authentication.
	 */

	/* Make sure that we and the peer are AUTH capable */
	if (!net->sctp.auth_enable || !asoc->peer.auth_capable)
		return false;

	/* set-up our fake chunk so that we can process it */
	auth.skb = chunk->auth_chunk;
	auth.asoc = chunk->asoc;
	auth.sctp_hdr = chunk->sctp_hdr;
	auth.chunk_hdr = (struct sctp_chunkhdr *)
				skb_push(chunk->auth_chunk,
					 sizeof(struct sctp_chunkhdr));
	skb_pull(chunk->auth_chunk, sizeof(struct sctp_chunkhdr));
	auth.transport = chunk->transport;

	return sctp_sf_authenticate(asoc, &auth) == SCTP_IERROR_NO_ERROR;
}