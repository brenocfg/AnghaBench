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
struct sctp_errhdr {int /*<<< orphan*/  cause; } ;
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {TYPE_2__* skb; TYPE_1__* chunk_hdr; } ;
struct sctp_addiphdr {int dummy; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  length; } ;
struct sctp_addip_param {scalar_t__ crr_id; TYPE_3__ param_hdr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_INV_PARAM ; 
 int /*<<< orphan*/  SCTP_ERROR_NO_ERROR ; 
 int /*<<< orphan*/  SCTP_ERROR_REQ_REFUSED ; 
#define  SCTP_PARAM_ERR_CAUSE 129 
#define  SCTP_PARAM_SUCCESS_REPORT 128 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 sctp_get_asconf_response(struct sctp_chunk *asconf_ack,
				       struct sctp_addip_param *asconf_param,
				       int no_err)
{
	struct sctp_addip_param	*asconf_ack_param;
	struct sctp_errhdr *err_param;
	int asconf_ack_len;
	__be16 err_code;
	int length;

	if (no_err)
		err_code = SCTP_ERROR_NO_ERROR;
	else
		err_code = SCTP_ERROR_REQ_REFUSED;

	asconf_ack_len = ntohs(asconf_ack->chunk_hdr->length) -
			 sizeof(struct sctp_chunkhdr);

	/* Skip the addiphdr from the asconf_ack chunk and store a pointer to
	 * the first asconf_ack parameter.
	 */
	length = sizeof(struct sctp_addiphdr);
	asconf_ack_param = (struct sctp_addip_param *)(asconf_ack->skb->data +
						       length);
	asconf_ack_len -= length;

	while (asconf_ack_len > 0) {
		if (asconf_ack_param->crr_id == asconf_param->crr_id) {
			switch (asconf_ack_param->param_hdr.type) {
			case SCTP_PARAM_SUCCESS_REPORT:
				return SCTP_ERROR_NO_ERROR;
			case SCTP_PARAM_ERR_CAUSE:
				length = sizeof(*asconf_ack_param);
				err_param = (void *)asconf_ack_param + length;
				asconf_ack_len -= length;
				if (asconf_ack_len > 0)
					return err_param->cause;
				else
					return SCTP_ERROR_INV_PARAM;
				break;
			default:
				return SCTP_ERROR_INV_PARAM;
			}
		}

		length = ntohs(asconf_ack_param->param_hdr.length);
		asconf_ack_param = (void *)asconf_ack_param + length;
		asconf_ack_len -= length;
	}

	return err_code;
}