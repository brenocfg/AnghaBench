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
struct mid_q_entry {int /*<<< orphan*/ * resp_buf; } ;
struct TCP_Server_Info {int /*<<< orphan*/ * smallbuf; } ;

/* Variables and functions */
 int cifs_discard_remaining_data (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  dequeue_mid (struct mid_q_entry*,int) ; 

__attribute__((used)) static int
__cifs_readv_discard(struct TCP_Server_Info *server, struct mid_q_entry *mid,
		     bool malformed)
{
	int length;

	length = cifs_discard_remaining_data(server);
	dequeue_mid(mid, malformed);
	mid->resp_buf = server->smallbuf;
	server->smallbuf = NULL;
	return length;
}