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
typedef  int uint16_t ;

/* Variables and functions */
 int PACKET_FANOUT_CPU ; 
 int PACKET_FANOUT_FLAG_UNIQUEID ; 
 int PACKET_FANOUT_HASH ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sock_fanout_getopts (int,int*,int*) ; 
 int sock_fanout_open (int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_unique_fanout_group_ids(void)
{
	int fds[3];
	uint16_t typeflags, first_group_id, second_group_id;

	fprintf(stderr, "test: unique ids\n");

	fds[0] = sock_fanout_open(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FLAG_UNIQUEID, 0);
	if (fds[0] == -1) {
		fprintf(stderr, "ERROR: failed to create a unique id group.\n");
		exit(1);
	}

	sock_fanout_getopts(fds[0], &typeflags, &first_group_id);
	if (typeflags != PACKET_FANOUT_HASH) {
		fprintf(stderr, "ERROR: unexpected typeflags %x\n", typeflags);
		exit(1);
	}

	if (sock_fanout_open(PACKET_FANOUT_CPU, first_group_id) != -1) {
		fprintf(stderr, "ERROR: joined group with wrong type.\n");
		exit(1);
	}

	fds[1] = sock_fanout_open(PACKET_FANOUT_HASH, first_group_id);
	if (fds[1] == -1) {
		fprintf(stderr,
			"ERROR: failed to join previously created group.\n");
		exit(1);
	}

	fds[2] = sock_fanout_open(PACKET_FANOUT_HASH |
				  PACKET_FANOUT_FLAG_UNIQUEID, 0);
	if (fds[2] == -1) {
		fprintf(stderr,
			"ERROR: failed to create a second unique id group.\n");
		exit(1);
	}

	sock_fanout_getopts(fds[2], &typeflags, &second_group_id);
	if (sock_fanout_open(PACKET_FANOUT_HASH | PACKET_FANOUT_FLAG_UNIQUEID,
			     second_group_id) != -1) {
		fprintf(stderr,
			"ERROR: specified a group id when requesting unique id\n");
		exit(1);
	}

	if (close(fds[0]) || close(fds[1]) || close(fds[2])) {
		fprintf(stderr, "ERROR: closing sockets\n");
		exit(1);
	}
}