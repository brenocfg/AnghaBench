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
typedef  int /*<<< orphan*/  val ;
struct testcase {int tlen; int gso_len; int r_num_mss; int r_len_last; scalar_t__ tfail; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int CONST_MSS_V4 ; 
 int CONST_MSS_V6 ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOL_UDP ; 
 int /*<<< orphan*/  UDP_SEGMENT ; 
 scalar_t__ cfg_do_setsockopt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int recv_one (int,int /*<<< orphan*/ ) ; 
 int send_one (int,int,int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void run_one(struct testcase *test, int fdt, int fdr,
		    struct sockaddr *addr, socklen_t alen)
{
	int i, ret, val, mss;
	bool sent;

	fprintf(stderr, "ipv%d tx:%d gso:%d %s\n",
			addr->sa_family == AF_INET ? 4 : 6,
			test->tlen, test->gso_len,
			test->tfail ? "(fail)" : "");

	val = test->gso_len;
	if (cfg_do_setsockopt) {
		if (setsockopt(fdt, SOL_UDP, UDP_SEGMENT, &val, sizeof(val)))
			error(1, errno, "setsockopt udp segment");
	}

	sent = send_one(fdt, test->tlen, test->gso_len, addr, alen);
	if (sent && test->tfail)
		error(1, 0, "send succeeded while expecting failure");
	if (!sent && !test->tfail)
		error(1, 0, "send failed while expecting success");
	if (!sent)
		return;

	if (test->gso_len)
		mss = test->gso_len;
	else
		mss = addr->sa_family == AF_INET ? CONST_MSS_V4 : CONST_MSS_V6;


	/* Recv all full MSS datagrams */
	for (i = 0; i < test->r_num_mss; i++) {
		ret = recv_one(fdr, 0);
		if (ret != mss)
			error(1, 0, "recv.%d: %d != %d", i, ret, mss);
	}

	/* Recv the non-full last datagram, if tlen was not a multiple of mss */
	if (test->r_len_last) {
		ret = recv_one(fdr, 0);
		if (ret != test->r_len_last)
			error(1, 0, "recv.%d: %d != %d (last)",
			      i, ret, test->r_len_last);
	}

	/* Verify received all data */
	ret = recv_one(fdr, MSG_DONTWAIT);
	if (ret)
		error(1, 0, "recv: unexpected datagram");
}