#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ead_msg_cmd {scalar_t__ data; void* timeout; void* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EAD_CMD_NORMAL ; 
 struct ead_msg_cmd* EAD_ENC_DATA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAD_TYPE_RESULT_CMD ; 
 int /*<<< orphan*/  EAD_TYPE_SEND_CMD ; 
 struct ead_msg_cmd* cmd ; 
 int /*<<< orphan*/  ead_encrypt_message (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  handle_cmd_data ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 TYPE_1__* msg ; 
 int send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
send_command(const char *command)
{
	struct ead_msg_cmd *cmd = EAD_ENC_DATA(msg, cmd);

	msg->type = htonl(EAD_TYPE_SEND_CMD);
	cmd->type = htons(EAD_CMD_NORMAL);
	cmd->timeout = htons(10);
	strncpy((char *)cmd->data, command, 1024);
	ead_encrypt_message(msg, sizeof(struct ead_msg_cmd) + strlen(command) + 1);
	return send_packet(EAD_TYPE_RESULT_CMD, handle_cmd_data, 1);
}