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
struct TYPE_2__ {void* length; int /*<<< orphan*/  type; } ;
struct sctp_hmac_algo_param {TYPE_1__ param_hdr; void** hmac_ids; } ;
struct sctp_endpoint {struct sctp_hmac_algo_param* auth_chunk_list; struct sctp_hmac_algo_param* auth_hmacs_list; } ;
struct sctp_chunks_param {TYPE_1__ param_hdr; void** hmac_ids; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SCTP_AUTH_HMAC_ID_SHA1 ; 
 int /*<<< orphan*/  SCTP_AUTH_NUM_HMACS ; 
 scalar_t__ SCTP_NUM_CHUNK_TYPES ; 
 int /*<<< orphan*/  SCTP_PARAM_CHUNKS ; 
 int /*<<< orphan*/  SCTP_PARAM_HMAC_ALGO ; 
 int /*<<< orphan*/  hmac_ids ; 
 void* htons (int) ; 
 int /*<<< orphan*/  kfree (struct sctp_hmac_algo_param*) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int sctp_auth_init_hmacs (struct sctp_endpoint*,int /*<<< orphan*/ ) ; 
 scalar_t__ struct_size (struct sctp_hmac_algo_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sctp_auth_init(struct sctp_endpoint *ep, gfp_t gfp)
{
	int err = -ENOMEM;

	/* Allocate space for HMACS and CHUNKS authentication
	 * variables.  There are arrays that we encode directly
	 * into parameters to make the rest of the operations easier.
	 */
	if (!ep->auth_hmacs_list) {
		struct sctp_hmac_algo_param *auth_hmacs;

		auth_hmacs = kzalloc(struct_size(auth_hmacs, hmac_ids,
						 SCTP_AUTH_NUM_HMACS), gfp);
		if (!auth_hmacs)
			goto nomem;
		/* Initialize the HMACS parameter.
		 * SCTP-AUTH: Section 3.3
		 *    Every endpoint supporting SCTP chunk authentication MUST
		 *    support the HMAC based on the SHA-1 algorithm.
		 */
		auth_hmacs->param_hdr.type = SCTP_PARAM_HMAC_ALGO;
		auth_hmacs->param_hdr.length =
				htons(sizeof(struct sctp_paramhdr) + 2);
		auth_hmacs->hmac_ids[0] = htons(SCTP_AUTH_HMAC_ID_SHA1);
		ep->auth_hmacs_list = auth_hmacs;
	}

	if (!ep->auth_chunk_list) {
		struct sctp_chunks_param *auth_chunks;

		auth_chunks = kzalloc(sizeof(*auth_chunks) +
				      SCTP_NUM_CHUNK_TYPES, gfp);
		if (!auth_chunks)
			goto nomem;
		/* Initialize the CHUNKS parameter */
		auth_chunks->param_hdr.type = SCTP_PARAM_CHUNKS;
		auth_chunks->param_hdr.length =
				htons(sizeof(struct sctp_paramhdr));
		ep->auth_chunk_list = auth_chunks;
	}

	/* Allocate and initialize transorms arrays for supported
	 * HMACs.
	 */
	err = sctp_auth_init_hmacs(ep, gfp);
	if (err)
		goto nomem;

	return 0;

nomem:
	/* Free all allocations */
	kfree(ep->auth_hmacs_list);
	kfree(ep->auth_chunk_list);
	ep->auth_hmacs_list = NULL;
	ep->auth_chunk_list = NULL;
	return err;
}