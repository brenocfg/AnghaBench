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
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ CLOCK_TAI ; 
 scalar_t__ PF_INET ; 
 scalar_t__ cfg_clockid ; 
 int /*<<< orphan*/ * cfg_in ; 
 int cfg_num_pkt ; 
 int /*<<< orphan*/ * cfg_out ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_recv_one (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_recv_verify_empty (int) ; 
 int /*<<< orphan*/  do_send_one (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,char*) ; 
 int /*<<< orphan*/  gettime_ns () ; 
 int /*<<< orphan*/  glob_tstart ; 
 int setup_rx (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int setup_tx (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_test(struct sockaddr *addr, socklen_t alen)
{
	int fdt, fdr, i;

	fprintf(stderr, "\nSO_TXTIME ipv%c clock %s\n",
			addr->sa_family == PF_INET ? '4' : '6',
			cfg_clockid == CLOCK_TAI ? "tai" : "monotonic");

	fdt = setup_tx(addr, alen);
	fdr = setup_rx(addr, alen);

	glob_tstart = gettime_ns();

	for (i = 0; i < cfg_num_pkt; i++)
		do_send_one(fdt, &cfg_in[i]);
	for (i = 0; i < cfg_num_pkt; i++)
		do_recv_one(fdr, &cfg_out[i]);

	do_recv_verify_empty(fdr);

	if (close(fdr))
		error(1, errno, "close r");
	if (close(fdt))
		error(1, errno, "close t");
}