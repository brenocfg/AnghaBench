#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ead_msg_auth {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {void* len; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  B ; 
 struct ead_msg_auth* EAD_DATA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAD_TYPE_DONE_AUTH ; 
 int EAD_TYPE_SEND_AUTH ; 
 struct ead_msg_auth* auth ; 
 int /*<<< orphan*/  ead_set_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_done_auth ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* msg ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  prepare_password () ; 
 int send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skey ; 
 int /*<<< orphan*/  t_clientgetkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t_clientpasswd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_clientresponse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc ; 

__attribute__((used)) static int
send_auth(void)
{
	struct ead_msg_auth *auth = EAD_DATA(msg, auth);

	prepare_password();
	t_clientpasswd(tc, password);
	skey = t_clientgetkey(tc, &B);
	if (!skey)
		return 0;

	ead_set_key(skey);
	msg->type = htonl(EAD_TYPE_SEND_AUTH);
	msg->len = htonl(sizeof(struct ead_msg_auth));
	memcpy(auth->data, t_clientresponse(tc), sizeof(auth->data));
	return send_packet(EAD_TYPE_DONE_AUTH, handle_done_auth, 1);
}