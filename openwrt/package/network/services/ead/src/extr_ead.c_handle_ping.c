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
struct ead_packet {int dummy; } ;
struct ead_msg_pong {int /*<<< orphan*/  auth_type; scalar_t__* name; } ;
struct ead_msg {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {struct ead_msg msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAD_AUTH_MD5 ; 
 struct ead_msg_pong* EAD_DATA (struct ead_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* pktbuf ; 
 struct ead_msg_pong* pong ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
handle_ping(struct ead_packet *pkt, int len, int *nstate)
{
	struct ead_msg *msg = &pktbuf->msg;
	struct ead_msg_pong *pong = EAD_DATA(msg, pong);
	int slen;

	slen = strlen(dev_name);
	if (slen > 1024)
		slen = 1024;

	msg->len = htonl(sizeof(struct ead_msg_pong) + slen);
	strncpy(pong->name, dev_name, slen);
	pong->name[slen] = 0;
	pong->auth_type = htons(EAD_AUTH_MD5);

	return true;
}