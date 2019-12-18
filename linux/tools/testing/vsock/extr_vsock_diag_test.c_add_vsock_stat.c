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
struct vsock_diag_msg {int dummy; } ;
struct vsock_stat {int /*<<< orphan*/  list; struct vsock_diag_msg msg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct vsock_stat* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void add_vsock_stat(struct list_head *sockets,
			   const struct vsock_diag_msg *resp)
{
	struct vsock_stat *st;

	st = malloc(sizeof(*st));
	if (!st) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	st->msg = *resp;
	list_add_tail(&st->list, sockets);
}