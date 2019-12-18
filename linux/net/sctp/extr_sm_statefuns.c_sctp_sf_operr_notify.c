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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
struct sctp_operr_chunk {int dummy; } ;
struct sctp_errhdr {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {scalar_t__ chunk_end; int /*<<< orphan*/  chunk_hdr; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_PROCESS_OPERR ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 int sctp_sf_pdiscard (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_paramlen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,void*,struct sctp_cmd_seq*) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 
 int /*<<< orphan*/  sctp_walk_errors (struct sctp_errhdr*,int /*<<< orphan*/ ) ; 

enum sctp_disposition sctp_sf_operr_notify(struct net *net,
					   const struct sctp_endpoint *ep,
					   const struct sctp_association *asoc,
					   const union sctp_subtype type,
					   void *arg,
					   struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *chunk = arg;
	struct sctp_errhdr *err;

	if (!sctp_vtag_verify(chunk, asoc))
		return sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);

	/* Make sure that the ERROR chunk has a valid length. */
	if (!sctp_chunk_length_valid(chunk, sizeof(struct sctp_operr_chunk)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);
	sctp_walk_errors(err, chunk->chunk_hdr);
	if ((void *)err != (void *)chunk->chunk_end)
		return sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
						  (void *)err, commands);

	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_OPERR,
			SCTP_CHUNK(chunk));

	return SCTP_DISPOSITION_CONSUME;
}