#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_paramhdr {int dummy; } ;
struct sctp_endpoint {struct sctp_chunks_param* auth_chunk_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct sctp_chunks_param {TYPE_1__ param_hdr; int /*<<< orphan*/ * chunks; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  size_t __u16 ;

/* Variables and functions */
 int EINVAL ; 
 size_t SCTP_NUM_CHUNK_TYPES ; 
 scalar_t__ __sctp_auth_cid (int /*<<< orphan*/ ,struct sctp_chunks_param*) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 

int sctp_auth_ep_add_chunkid(struct sctp_endpoint *ep, __u8 chunk_id)
{
	struct sctp_chunks_param *p = ep->auth_chunk_list;
	__u16 nchunks;
	__u16 param_len;

	/* If this chunk is already specified, we are done */
	if (__sctp_auth_cid(chunk_id, p))
		return 0;

	/* Check if we can add this chunk to the array */
	param_len = ntohs(p->param_hdr.length);
	nchunks = param_len - sizeof(struct sctp_paramhdr);
	if (nchunks == SCTP_NUM_CHUNK_TYPES)
		return -EINVAL;

	p->chunks[nchunks] = chunk_id;
	p->param_hdr.length = htons(param_len + 1);
	return 0;
}