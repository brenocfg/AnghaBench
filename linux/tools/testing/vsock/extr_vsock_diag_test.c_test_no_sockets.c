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

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_no_sockets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sock_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_vsock_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockets ; 

__attribute__((used)) static void test_no_sockets(unsigned int peer_cid)
{
	LIST_HEAD(sockets);

	read_vsock_stat(&sockets);

	check_no_sockets(&sockets);

	free_sock_stat(&sockets);
}