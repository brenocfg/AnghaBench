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
struct TYPE_2__ {int /*<<< orphan*/  CreditRequest; } ;
struct smb2_echo_rsp {TYPE_1__ sync_hdr; } ;
struct mid_q_entry {scalar_t__ mid_state; scalar_t__ resp_buf; struct TCP_Server_Info* callback_data; } ;
struct cifs_credits {int /*<<< orphan*/  instance; int /*<<< orphan*/  value; } ;
struct TCP_Server_Info {int /*<<< orphan*/  reconnect_instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_ECHO_OP ; 
 int /*<<< orphan*/  DeleteMidQEntry (struct mid_q_entry*) ; 
 scalar_t__ MID_RESPONSE_MALFORMED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  add_credits (struct TCP_Server_Info*,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smb2_echo_callback(struct mid_q_entry *mid)
{
	struct TCP_Server_Info *server = mid->callback_data;
	struct smb2_echo_rsp *rsp = (struct smb2_echo_rsp *)mid->resp_buf;
	struct cifs_credits credits = { .value = 0, .instance = 0 };

	if (mid->mid_state == MID_RESPONSE_RECEIVED
	    || mid->mid_state == MID_RESPONSE_MALFORMED) {
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
	}

	DeleteMidQEntry(mid);
	add_credits(server, &credits, CIFS_ECHO_OP);
}