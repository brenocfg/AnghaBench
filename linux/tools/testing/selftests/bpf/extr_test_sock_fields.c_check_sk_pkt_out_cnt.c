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
struct bpf_spinlock_cnt {int cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int*,struct bpf_spinlock_cnt*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sk_pkt_out_cnt10_fd ; 
 int /*<<< orphan*/  sk_pkt_out_cnt_fd ; 

__attribute__((used)) static void check_sk_pkt_out_cnt(int accept_fd, int cli_fd)
{
	struct bpf_spinlock_cnt pkt_out_cnt = {}, pkt_out_cnt10 = {};
	int err;

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	err = bpf_map_lookup_elem(sk_pkt_out_cnt_fd, &accept_fd, &pkt_out_cnt);
	if (!err)
		err = bpf_map_lookup_elem(sk_pkt_out_cnt10_fd, &accept_fd,
					  &pkt_out_cnt10);

	/* The bpf prog only counts for fullsock and
	 * passive conneciton did not become fullsock until 3WHS
	 * had been finished.
	 * The bpf prog only counted two data packet out but we
	 * specially init accept_fd's pkt_out_cnt by 2 in
	 * init_sk_storage().  Hence, 4 here.
	 */
	CHECK(err || pkt_out_cnt.cnt != 4 || pkt_out_cnt10.cnt != 40,
	      "bpf_map_lookup_elem(sk_pkt_out_cnt, &accept_fd)",
	      "err:%d errno:%d pkt_out_cnt:%u pkt_out_cnt10:%u",
	      err, errno, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);

	pkt_out_cnt.cnt = ~0;
	pkt_out_cnt10.cnt = ~0;
	err = bpf_map_lookup_elem(sk_pkt_out_cnt_fd, &cli_fd, &pkt_out_cnt);
	if (!err)
		err = bpf_map_lookup_elem(sk_pkt_out_cnt10_fd, &cli_fd,
					  &pkt_out_cnt10);
	/* Active connection is fullsock from the beginning.
	 * 1 SYN and 1 ACK during 3WHS
	 * 2 Acks on data packet.
	 *
	 * The bpf_prog initialized it to 0xeB9F.
	 */
	CHECK(err || pkt_out_cnt.cnt != 0xeB9F + 4 ||
	      pkt_out_cnt10.cnt != 0xeB9F + 40,
	      "bpf_map_lookup_elem(sk_pkt_out_cnt, &cli_fd)",
	      "err:%d errno:%d pkt_out_cnt:%u pkt_out_cnt10:%u",
	      err, errno, pkt_out_cnt.cnt, pkt_out_cnt10.cnt);
}