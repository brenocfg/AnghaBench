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
 int PACKET_FANOUT_FLAG_ROLLOVER ; 
 int PACKET_FANOUT_ROLLOVER ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int sock_fanout_open (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_control_single(void)
{
	fprintf(stderr, "test: control single socket\n");

	if (sock_fanout_open(PACKET_FANOUT_ROLLOVER |
			       PACKET_FANOUT_FLAG_ROLLOVER, 0) != -1) {
		fprintf(stderr, "ERROR: opened socket with dual rollover\n");
		exit(1);
	}
}