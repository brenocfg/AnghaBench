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
struct mid_q_entry {int dummy; } ;
struct TCP_Server_Info {char* bigbuf; char* smallbuf; int /*<<< orphan*/  pdu_size; scalar_t__ large_buf; } ;

/* Variables and functions */
 int handle_read_data (struct TCP_Server_Info*,struct mid_q_entry*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb3_handle_read_data(struct TCP_Server_Info *server, struct mid_q_entry *mid)
{
	char *buf = server->large_buf ? server->bigbuf : server->smallbuf;

	return handle_read_data(server, mid, buf, server->pdu_size,
				NULL, 0, 0);
}