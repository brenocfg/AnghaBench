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
 int PF_INET ; 
 scalar_t__ SOCK_STREAM ; 
 int SOF_TIMESTAMPING_TX_ACK ; 
 int SOF_TIMESTAMPING_TX_SCHED ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 
 scalar_t__ cfg_proto ; 
 scalar_t__ cfg_use_pf_packet ; 
 int /*<<< orphan*/  do_test (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_main(int family)
{
	fprintf(stderr, "family:       %s %s\n",
			family == PF_INET ? "INET" : "INET6",
			cfg_use_pf_packet ? "(PF_PACKET)" : "");

	fprintf(stderr, "test SND\n");
	do_test(family, SOF_TIMESTAMPING_TX_SOFTWARE);

	fprintf(stderr, "test ENQ\n");
	do_test(family, SOF_TIMESTAMPING_TX_SCHED);

	fprintf(stderr, "test ENQ + SND\n");
	do_test(family, SOF_TIMESTAMPING_TX_SCHED |
			SOF_TIMESTAMPING_TX_SOFTWARE);

	if (cfg_proto == SOCK_STREAM) {
		fprintf(stderr, "\ntest ACK\n");
		do_test(family, SOF_TIMESTAMPING_TX_ACK);

		fprintf(stderr, "\ntest SND + ACK\n");
		do_test(family, SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_TX_ACK);

		fprintf(stderr, "\ntest ENQ + SND + ACK\n");
		do_test(family, SOF_TIMESTAMPING_TX_SCHED |
				SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_TX_ACK);
	}
}