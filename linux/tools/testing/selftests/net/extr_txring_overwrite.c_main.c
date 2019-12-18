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
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int read_verify_pkt (int,char const) ; 
 int /*<<< orphan*/  send_pkt (int,char*,char const) ; 
 int setup_rx () ; 
 int setup_tx (char**) ; 

int main(int argc, char **argv)
{
	const char payload_patterns[] = "ab";
	char *ring;
	int fdr, fdt, ret = 0;

	fdr = setup_rx();
	fdt = setup_tx(&ring);

	send_pkt(fdt, ring, payload_patterns[0]);
	send_pkt(fdt, ring, payload_patterns[1]);

	ret |= read_verify_pkt(fdr, payload_patterns[0]);
	ret |= read_verify_pkt(fdr, payload_patterns[1]);

	if (close(fdt))
		error(1, errno, "close t");
	if (close(fdr))
		error(1, errno, "close r");

	return ret;
}