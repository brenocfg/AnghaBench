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
struct bpf_object {int dummy; } ;
typedef  int socklen_t ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  SOL_IP ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int prog_attach (struct bpf_object*,int,char*) ; 
 int prog_detach (struct bpf_object*,int,char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int run_getsockopt_test(struct bpf_object *obj, int cg_parent,
			       int cg_child, int sock_fd)
{
	socklen_t optlen;
	__u8 buf;
	int err;

	/* Set IP_TOS to the expected value (0x80). */

	buf = 0x80;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	if (err < 0) {
		log_err("Failed to call setsockopt(IP_TOS)");
		goto detach;
	}

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (err) {
		log_err("Failed to call getsockopt(IP_TOS)");
		goto detach;
	}

	if (buf != 0x80) {
		log_err("Unexpected getsockopt 0x%x != 0x80 without BPF", buf);
		err = -1;
		goto detach;
	}

	/* Attach child program and make sure it returns new value:
	 * - kernel:      -> 0x80
	 * - child:  0x80 -> 0x90
	 */

	err = prog_attach(obj, cg_child, "cgroup/getsockopt/child");
	if (err)
		goto detach;

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (err) {
		log_err("Failed to call getsockopt(IP_TOS)");
		goto detach;
	}

	if (buf != 0x90) {
		log_err("Unexpected getsockopt 0x%x != 0x90", buf);
		err = -1;
		goto detach;
	}

	/* Attach parent program and make sure it returns new value:
	 * - kernel:      -> 0x80
	 * - child:  0x80 -> 0x90
	 * - parent: 0x90 -> 0xA0
	 */

	err = prog_attach(obj, cg_parent, "cgroup/getsockopt/parent");
	if (err)
		goto detach;

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (err) {
		log_err("Failed to call getsockopt(IP_TOS)");
		goto detach;
	}

	if (buf != 0xA0) {
		log_err("Unexpected getsockopt 0x%x != 0xA0", buf);
		err = -1;
		goto detach;
	}

	/* Setting unexpected initial sockopt should return EPERM:
	 * - kernel: -> 0x40
	 * - child:  unexpected 0x40, EPERM
	 * - parent: unexpected 0x40, EPERM
	 */

	buf = 0x40;
	if (setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1) < 0) {
		log_err("Failed to call setsockopt(IP_TOS)");
		goto detach;
	}

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (!err) {
		log_err("Unexpected success from getsockopt(IP_TOS)");
		goto detach;
	}

	/* Detach child program and make sure we still get EPERM:
	 * - kernel: -> 0x40
	 * - parent: unexpected 0x40, EPERM
	 */

	err = prog_detach(obj, cg_child, "cgroup/getsockopt/child");
	if (err) {
		log_err("Failed to detach child program");
		goto detach;
	}

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (!err) {
		log_err("Unexpected success from getsockopt(IP_TOS)");
		goto detach;
	}

	/* Set initial value to the one the parent program expects:
	 * - kernel:      -> 0x90
	 * - parent: 0x90 -> 0xA0
	 */

	buf = 0x90;
	err = setsockopt(sock_fd, SOL_IP, IP_TOS, &buf, 1);
	if (err < 0) {
		log_err("Failed to call setsockopt(IP_TOS)");
		goto detach;
	}

	buf = 0x00;
	optlen = 1;
	err = getsockopt(sock_fd, SOL_IP, IP_TOS, &buf, &optlen);
	if (err) {
		log_err("Failed to call getsockopt(IP_TOS)");
		goto detach;
	}

	if (buf != 0xA0) {
		log_err("Unexpected getsockopt 0x%x != 0xA0", buf);
		err = -1;
		goto detach;
	}

detach:
	prog_detach(obj, cg_child, "cgroup/getsockopt/child");
	prog_detach(obj, cg_parent, "cgroup/getsockopt/parent");

	return err;
}