#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bpf_tcp_sock {int state; scalar_t__ family; scalar_t__ protocol; scalar_t__ src_port; scalar_t__ dst_port; int data_segs_out; int data_segs_in; int bytes_acked; int snd_cwnd; int bytes_received; scalar_t__ total_retrans; scalar_t__* dst_ip6; scalar_t__* src_ip6; } ;
struct bpf_sock {int state; scalar_t__ family; scalar_t__ protocol; scalar_t__ src_port; scalar_t__ dst_port; int data_segs_out; int data_segs_in; int bytes_acked; int snd_cwnd; int bytes_received; scalar_t__ total_retrans; scalar_t__* dst_ip6; scalar_t__* src_ip6; } ;
typedef  struct bpf_tcp_sock __u32 ;
struct TYPE_4__ {scalar_t__ sin6_port; } ;
struct TYPE_3__ {scalar_t__ sin6_port; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,...) ; 
 int DATA_LEN ; 
 scalar_t__ IPPROTO_TCP ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bpf_tcp_sock*) ; 
 TYPE_2__ cli_sa6 ; 
 int /*<<< orphan*/  egress_cli_idx ; 
 int /*<<< orphan*/  egress_linum_idx ; 
 int /*<<< orphan*/  egress_srv_idx ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  ingress_linum_idx ; 
 int /*<<< orphan*/  ingress_listen_idx ; 
 int /*<<< orphan*/  linum_map_fd ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 int /*<<< orphan*/  print_sk (struct bpf_tcp_sock*) ; 
 int /*<<< orphan*/  print_tp (struct bpf_tcp_sock*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sk_map_fd ; 
 TYPE_1__ srv_sa6 ; 
 int /*<<< orphan*/  tp_map_fd ; 

__attribute__((used)) static void check_result(void)
{
	struct bpf_tcp_sock srv_tp, cli_tp, listen_tp;
	struct bpf_sock srv_sk, cli_sk, listen_sk;
	__u32 ingress_linum, egress_linum;
	int err;

	err = bpf_map_lookup_elem(linum_map_fd, &egress_linum_idx,
				  &egress_linum);
	CHECK(err == -1, "bpf_map_lookup_elem(linum_map_fd)",
	      "err:%d errno:%d", err, errno);

	err = bpf_map_lookup_elem(linum_map_fd, &ingress_linum_idx,
				  &ingress_linum);
	CHECK(err == -1, "bpf_map_lookup_elem(linum_map_fd)",
	      "err:%d errno:%d", err, errno);

	err = bpf_map_lookup_elem(sk_map_fd, &egress_srv_idx, &srv_sk);
	CHECK(err == -1, "bpf_map_lookup_elem(sk_map_fd, &egress_srv_idx)",
	      "err:%d errno:%d", err, errno);
	err = bpf_map_lookup_elem(tp_map_fd, &egress_srv_idx, &srv_tp);
	CHECK(err == -1, "bpf_map_lookup_elem(tp_map_fd, &egress_srv_idx)",
	      "err:%d errno:%d", err, errno);

	err = bpf_map_lookup_elem(sk_map_fd, &egress_cli_idx, &cli_sk);
	CHECK(err == -1, "bpf_map_lookup_elem(sk_map_fd, &egress_cli_idx)",
	      "err:%d errno:%d", err, errno);
	err = bpf_map_lookup_elem(tp_map_fd, &egress_cli_idx, &cli_tp);
	CHECK(err == -1, "bpf_map_lookup_elem(tp_map_fd, &egress_cli_idx)",
	      "err:%d errno:%d", err, errno);

	err = bpf_map_lookup_elem(sk_map_fd, &ingress_listen_idx, &listen_sk);
	CHECK(err == -1, "bpf_map_lookup_elem(sk_map_fd, &ingress_listen_idx)",
	      "err:%d errno:%d", err, errno);
	err = bpf_map_lookup_elem(tp_map_fd, &ingress_listen_idx, &listen_tp);
	CHECK(err == -1, "bpf_map_lookup_elem(tp_map_fd, &ingress_listen_idx)",
	      "err:%d errno:%d", err, errno);

	printf("listen_sk: ");
	print_sk(&listen_sk);
	printf("\n");

	printf("srv_sk: ");
	print_sk(&srv_sk);
	printf("\n");

	printf("cli_sk: ");
	print_sk(&cli_sk);
	printf("\n");

	printf("listen_tp: ");
	print_tp(&listen_tp);
	printf("\n");

	printf("srv_tp: ");
	print_tp(&srv_tp);
	printf("\n");

	printf("cli_tp: ");
	print_tp(&cli_tp);
	printf("\n");

	CHECK(listen_sk.state != 10 ||
	      listen_sk.family != AF_INET6 ||
	      listen_sk.protocol != IPPROTO_TCP ||
	      memcmp(listen_sk.src_ip6, &in6addr_loopback,
		     sizeof(listen_sk.src_ip6)) ||
	      listen_sk.dst_ip6[0] || listen_sk.dst_ip6[1] ||
	      listen_sk.dst_ip6[2] || listen_sk.dst_ip6[3] ||
	      listen_sk.src_port != ntohs(srv_sa6.sin6_port) ||
	      listen_sk.dst_port,
	      "Unexpected listen_sk",
	      "Check listen_sk output. ingress_linum:%u",
	      ingress_linum);

	CHECK(srv_sk.state == 10 ||
	      !srv_sk.state ||
	      srv_sk.family != AF_INET6 ||
	      srv_sk.protocol != IPPROTO_TCP ||
	      memcmp(srv_sk.src_ip6, &in6addr_loopback,
		     sizeof(srv_sk.src_ip6)) ||
	      memcmp(srv_sk.dst_ip6, &in6addr_loopback,
		     sizeof(srv_sk.dst_ip6)) ||
	      srv_sk.src_port != ntohs(srv_sa6.sin6_port) ||
	      srv_sk.dst_port != cli_sa6.sin6_port,
	      "Unexpected srv_sk", "Check srv_sk output. egress_linum:%u",
	      egress_linum);

	CHECK(cli_sk.state == 10 ||
	      !cli_sk.state ||
	      cli_sk.family != AF_INET6 ||
	      cli_sk.protocol != IPPROTO_TCP ||
	      memcmp(cli_sk.src_ip6, &in6addr_loopback,
		     sizeof(cli_sk.src_ip6)) ||
	      memcmp(cli_sk.dst_ip6, &in6addr_loopback,
		     sizeof(cli_sk.dst_ip6)) ||
	      cli_sk.src_port != ntohs(cli_sa6.sin6_port) ||
	      cli_sk.dst_port != srv_sa6.sin6_port,
	      "Unexpected cli_sk", "Check cli_sk output. egress_linum:%u",
	      egress_linum);

	CHECK(listen_tp.data_segs_out ||
	      listen_tp.data_segs_in ||
	      listen_tp.total_retrans ||
	      listen_tp.bytes_acked,
	      "Unexpected listen_tp", "Check listen_tp output. ingress_linum:%u",
	      ingress_linum);

	CHECK(srv_tp.data_segs_out != 2 ||
	      srv_tp.data_segs_in ||
	      srv_tp.snd_cwnd != 10 ||
	      srv_tp.total_retrans ||
	      srv_tp.bytes_acked != 2 * DATA_LEN,
	      "Unexpected srv_tp", "Check srv_tp output. egress_linum:%u",
	      egress_linum);

	CHECK(cli_tp.data_segs_out ||
	      cli_tp.data_segs_in != 2 ||
	      cli_tp.snd_cwnd != 10 ||
	      cli_tp.total_retrans ||
	      cli_tp.bytes_received != 2 * DATA_LEN,
	      "Unexpected cli_tp", "Check cli_tp output. egress_linum:%u",
	      egress_linum);
}