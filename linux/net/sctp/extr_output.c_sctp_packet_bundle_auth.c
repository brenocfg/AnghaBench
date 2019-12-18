#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_packet {scalar_t__ has_auth; TYPE_1__* transport; } ;
struct sctp_chunk {TYPE_3__* shkey; int /*<<< orphan*/  auth; TYPE_2__* chunk_hdr; } ;
struct sctp_association {int dummy; } ;
typedef  enum sctp_xmit { ____Placeholder_sctp_xmit } sctp_xmit ;
struct TYPE_6__ {int /*<<< orphan*/  key_id; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {struct sctp_association* asoc; } ;

/* Variables and functions */
 scalar_t__ SCTP_CID_AUTH ; 
 int SCTP_XMIT_OK ; 
 int __sctp_packet_append_chunk (struct sctp_packet*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_auth_shkey_hold (TYPE_3__*) ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_auth (struct sctp_association*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sctp_xmit sctp_packet_bundle_auth(struct sctp_packet *pkt,
					      struct sctp_chunk *chunk)
{
	struct sctp_association *asoc = pkt->transport->asoc;
	enum sctp_xmit retval = SCTP_XMIT_OK;
	struct sctp_chunk *auth;

	/* if we don't have an association, we can't do authentication */
	if (!asoc)
		return retval;

	/* See if this is an auth chunk we are bundling or if
	 * auth is already bundled.
	 */
	if (chunk->chunk_hdr->type == SCTP_CID_AUTH || pkt->has_auth)
		return retval;

	/* if the peer did not request this chunk to be authenticated,
	 * don't do it
	 */
	if (!chunk->auth)
		return retval;

	auth = sctp_make_auth(asoc, chunk->shkey->key_id);
	if (!auth)
		return retval;

	auth->shkey = chunk->shkey;
	sctp_auth_shkey_hold(auth->shkey);

	retval = __sctp_packet_append_chunk(pkt, auth);

	if (retval != SCTP_XMIT_OK)
		sctp_chunk_free(auth);

	return retval;
}