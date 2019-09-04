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
struct zcrypt_queue {int /*<<< orphan*/  online; TYPE_1__* queue; } ;
struct error_hdr {int reply_code; } ;
struct ap_message {struct error_hdr* message; } ;
struct TYPE_2__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  DBF_WARN ; 
 int EAGAIN ; 
 int EINVAL ; 
#define  REP82_ERROR_EVEN_MOD_IN_OPND 137 
#define  REP82_ERROR_INVALID_DOMAIN_PENDING 136 
#define  REP82_ERROR_INVALID_DOMAIN_PRECHECK 135 
#define  REP82_ERROR_INVALID_SPECIAL_CMD 134 
#define  REP82_ERROR_MACHINE_FAILURE 133 
#define  REP82_ERROR_MESSAGE_TYPE 132 
#define  REP82_ERROR_OPERAND_INVALID 131 
#define  REP82_ERROR_OPERAND_SIZE 130 
#define  REP82_ERROR_TRANSPORT_FAIL 129 
#define  REP88_ERROR_MESSAGE_MALFORMD 128 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  zcrypt_rescan_req ; 

__attribute__((used)) static inline int convert_error(struct zcrypt_queue *zq,
				struct ap_message *reply)
{
	struct error_hdr *ehdr = reply->message;
	int card = AP_QID_CARD(zq->queue->qid);
	int queue = AP_QID_QUEUE(zq->queue->qid);

	switch (ehdr->reply_code) {
	case REP82_ERROR_OPERAND_INVALID:
	case REP82_ERROR_OPERAND_SIZE:
	case REP82_ERROR_EVEN_MOD_IN_OPND:
	case REP88_ERROR_MESSAGE_MALFORMD:
	case REP82_ERROR_INVALID_DOMAIN_PRECHECK:
	case REP82_ERROR_INVALID_DOMAIN_PENDING:
	case REP82_ERROR_INVALID_SPECIAL_CMD:
	//   REP88_ERROR_INVALID_KEY		// '82' CEX2A
	//   REP88_ERROR_OPERAND		// '84' CEX2A
	//   REP88_ERROR_OPERAND_EVEN_MOD	// '85' CEX2A
		/* Invalid input data. */
		ZCRYPT_DBF(DBF_WARN,
			   "device=%02x.%04x reply=0x%02x => rc=EINVAL\n",
			   card, queue, ehdr->reply_code);
		return -EINVAL;
	case REP82_ERROR_MESSAGE_TYPE:
	//   REP88_ERROR_MESSAGE_TYPE		// '20' CEX2A
		/*
		 * To sent a message of the wrong type is a bug in the
		 * device driver. Send error msg, disable the device
		 * and then repeat the request.
		 */
		atomic_set(&zcrypt_rescan_req, 1);
		zq->online = 0;
		pr_err("Cryptographic device %02x.%04x failed and was set offline\n",
		       card, queue);
		ZCRYPT_DBF(DBF_ERR,
			   "device=%02x.%04x reply=0x%02x => online=0 rc=EAGAIN\n",
			   card, queue, ehdr->reply_code);
		return -EAGAIN;
	case REP82_ERROR_TRANSPORT_FAIL:
	case REP82_ERROR_MACHINE_FAILURE:
	//   REP88_ERROR_MODULE_FAILURE		// '10' CEX2A
		/* If a card fails disable it and repeat the request. */
		atomic_set(&zcrypt_rescan_req, 1);
		zq->online = 0;
		pr_err("Cryptographic device %02x.%04x failed and was set offline\n",
		       card, queue);
		ZCRYPT_DBF(DBF_ERR,
			   "device=%02x.%04x reply=0x%02x => online=0 rc=EAGAIN\n",
			   card, queue, ehdr->reply_code);
		return -EAGAIN;
	default:
		zq->online = 0;
		pr_err("Cryptographic device %02x.%04x failed and was set offline\n",
		       card, queue);
		ZCRYPT_DBF(DBF_ERR,
			   "device=%02x.%04x reply=0x%02x => online=0 rc=EAGAIN\n",
			   card, queue, ehdr->reply_code);
		return -EAGAIN;	/* repeat the request on a different device. */
	}
}