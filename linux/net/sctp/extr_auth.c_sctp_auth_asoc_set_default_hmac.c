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
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct sctp_hmac_algo_param {int /*<<< orphan*/ * hmac_ids; TYPE_1__ param_hdr; } ;
struct sctp_endpoint {scalar_t__* auth_hmacs; } ;
struct sctp_association {int default_hmac_id; struct sctp_endpoint* ep; } ;
typedef  size_t __u16 ;

/* Variables and functions */
 size_t SCTP_AUTH_HMAC_ID_MAX ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 

void sctp_auth_asoc_set_default_hmac(struct sctp_association *asoc,
				     struct sctp_hmac_algo_param *hmacs)
{
	struct sctp_endpoint *ep;
	__u16   id;
	int	i;
	int	n_params;

	/* if the default id is already set, use it */
	if (asoc->default_hmac_id)
		return;

	n_params = (ntohs(hmacs->param_hdr.length) -
		    sizeof(struct sctp_paramhdr)) >> 1;
	ep = asoc->ep;
	for (i = 0; i < n_params; i++) {
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the supported range */
		if (id > SCTP_AUTH_HMAC_ID_MAX)
			continue;

		/* If this TFM has been allocated, use this id */
		if (ep->auth_hmacs[id]) {
			asoc->default_hmac_id = id;
			break;
		}
	}
}