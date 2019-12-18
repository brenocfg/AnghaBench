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
struct mid_q_entry {char* resp_buf; int /*<<< orphan*/  multiRsp; scalar_t__ large_buf; } ;
struct TCP_Server_Info {int /*<<< orphan*/ * smallbuf; int /*<<< orphan*/ * bigbuf; scalar_t__ large_buf; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* check_trans2 ) (struct mid_q_entry*,struct TCP_Server_Info*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue_mid (struct mid_q_entry*,int) ; 
 scalar_t__ stub1 (struct mid_q_entry*,struct TCP_Server_Info*,char*,int) ; 

__attribute__((used)) static void
handle_mid(struct mid_q_entry *mid, struct TCP_Server_Info *server,
	   char *buf, int malformed)
{
	if (server->ops->check_trans2 &&
	    server->ops->check_trans2(mid, server, buf, malformed))
		return;
	mid->resp_buf = buf;
	mid->large_buf = server->large_buf;
	/* Was previous buf put in mpx struct for multi-rsp? */
	if (!mid->multiRsp) {
		/* smb buffer will be freed by user thread */
		if (server->large_buf)
			server->bigbuf = NULL;
		else
			server->smallbuf = NULL;
	}
	dequeue_mid(mid, malformed);
}