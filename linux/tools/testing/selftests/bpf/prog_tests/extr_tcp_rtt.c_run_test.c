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
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_SOCK_OPS ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCK_OPS ; 
 int bpf_map__fd (struct bpf_map*) ; 
 struct bpf_map* bpf_map__next (int /*<<< orphan*/ *,struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 int bpf_prog_attach (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect_to_server (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  send_byte (int) ; 
 scalar_t__ verify_sk (int,int,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_ack (int,int) ; 

__attribute__((used)) static int run_test(int cgroup_fd, int server_fd)
{
	struct bpf_prog_load_attr attr = {
		.prog_type = BPF_PROG_TYPE_SOCK_OPS,
		.file = "./tcp_rtt.o",
		.expected_attach_type = BPF_CGROUP_SOCK_OPS,
	};
	struct bpf_object *obj;
	struct bpf_map *map;
	int client_fd;
	int prog_fd;
	int map_fd;
	int err;

	err = bpf_prog_load_xattr(&attr, &obj, &prog_fd);
	if (err) {
		log_err("Failed to load BPF object");
		return -1;
	}

	map = bpf_map__next(NULL, obj);
	map_fd = bpf_map__fd(map);

	err = bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_SOCK_OPS, 0);
	if (err) {
		log_err("Failed to attach BPF program");
		goto close_bpf_object;
	}

	client_fd = connect_to_server(server_fd);
	if (client_fd < 0) {
		err = -1;
		goto close_bpf_object;
	}

	err += verify_sk(map_fd, client_fd, "syn-ack",
			 /*invoked=*/1,
			 /*dsack_dups=*/0,
			 /*delivered=*/1,
			 /*delivered_ce=*/0,
			 /*icsk_retransmits=*/0);

	send_byte(client_fd);
	if (wait_for_ack(client_fd, 100) < 0) {
		err = -1;
		goto close_client_fd;
	}


	err += verify_sk(map_fd, client_fd, "first payload byte",
			 /*invoked=*/2,
			 /*dsack_dups=*/0,
			 /*delivered=*/2,
			 /*delivered_ce=*/0,
			 /*icsk_retransmits=*/0);

close_client_fd:
	close(client_fd);

close_bpf_object:
	bpf_object__close(obj);
	return err;
}