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
struct p9_trans_fd {scalar_t__ wr; scalar_t__ rd; int /*<<< orphan*/  conn; } ;
struct p9_client {int /*<<< orphan*/  status; struct p9_trans_fd* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnected ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct p9_trans_fd*) ; 
 int /*<<< orphan*/  p9_conn_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p9_fd_close(struct p9_client *client)
{
	struct p9_trans_fd *ts;

	if (!client)
		return;

	ts = client->trans;
	if (!ts)
		return;

	client->status = Disconnected;

	p9_conn_destroy(&ts->conn);

	if (ts->rd)
		fput(ts->rd);
	if (ts->wr)
		fput(ts->wr);

	kfree(ts);
}