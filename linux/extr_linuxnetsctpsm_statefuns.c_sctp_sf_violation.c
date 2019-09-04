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
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int SCTP_DISPOSITION_VIOLATION ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 

enum sctp_disposition sctp_sf_violation(struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *chunk = arg;

	/* Make sure that the chunk has a valid length. */
	if (!sctp_chunk_length_valid(chunk, sizeof(struct sctp_chunkhdr)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	return SCTP_DISPOSITION_VIOLATION;
}