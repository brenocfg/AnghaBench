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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  print_vsock_stats (int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void check_no_sockets(struct list_head *head)
{
	if (!list_empty(head)) {
		fprintf(stderr, "expected no sockets\n");
		print_vsock_stats(stderr, head);
		exit(1);
	}
}