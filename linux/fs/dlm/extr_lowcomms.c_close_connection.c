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
struct connection {int /*<<< orphan*/  flags; int /*<<< orphan*/  sock_mutex; scalar_t__ retries; int /*<<< orphan*/ * rx_page; struct connection* othercon; int /*<<< orphan*/ * sock; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  rwork; int /*<<< orphan*/  swork; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CLOSING ; 
 int /*<<< orphan*/  CF_READ_PENDING ; 
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_connection(struct connection *con, bool and_other,
			     bool tx, bool rx)
{
	bool closing = test_and_set_bit(CF_CLOSING, &con->flags);

	if (tx && !closing && cancel_work_sync(&con->swork)) {
		log_print("canceled swork for node %d", con->nodeid);
		clear_bit(CF_WRITE_PENDING, &con->flags);
	}
	if (rx && !closing && cancel_work_sync(&con->rwork)) {
		log_print("canceled rwork for node %d", con->nodeid);
		clear_bit(CF_READ_PENDING, &con->flags);
	}

	mutex_lock(&con->sock_mutex);
	if (con->sock) {
		restore_callbacks(con->sock);
		sock_release(con->sock);
		con->sock = NULL;
	}
	if (con->othercon && and_other) {
		/* Will only re-enter once. */
		close_connection(con->othercon, false, true, true);
	}
	if (con->rx_page) {
		__free_page(con->rx_page);
		con->rx_page = NULL;
	}

	con->retries = 0;
	mutex_unlock(&con->sock_mutex);
	clear_bit(CF_CLOSING, &con->flags);
}