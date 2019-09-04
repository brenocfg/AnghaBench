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
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_payload(void *pay, size_t len)
{
	struct ethhdr *eth = pay;

	if (len < sizeof(struct ethhdr)) {
		fprintf(stderr, "test_payload: packet too "
			"small: %zu bytes!\n", len);
		exit(1);
	}

	if (eth->h_proto != htons(ETH_P_IP)) {
		fprintf(stderr, "test_payload: wrong ethernet "
			"type: 0x%x!\n", ntohs(eth->h_proto));
		exit(1);
	}
}