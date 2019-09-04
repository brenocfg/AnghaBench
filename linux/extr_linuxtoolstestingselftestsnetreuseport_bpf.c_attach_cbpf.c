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
typedef  int /*<<< orphan*/  uint16_t ;
struct sock_fprog {struct sock_filter* filter; int /*<<< orphan*/  len; } ;
struct sock_filter {int member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct sock_filter*) ; 
 int BPF_A ; 
 int BPF_ABS ; 
 int BPF_ALU ; 
 int BPF_LD ; 
 int BPF_MOD ; 
 int BPF_RET ; 
 int BPF_W ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ATTACH_REUSEPORT_CBPF ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_fprog*,int) ; 

__attribute__((used)) static void attach_cbpf(int fd, uint16_t mod)
{
	struct sock_filter code[] = {
		/* A = (uint32_t)skb[0] */
		{ BPF_LD  | BPF_W | BPF_ABS, 0, 0, 0 },
		/* A = A % mod */
		{ BPF_ALU | BPF_MOD, 0, 0, mod },
		/* return A */
		{ BPF_RET | BPF_A, 0, 0, 0 },
	};
	struct sock_fprog p = {
		.len = ARRAY_SIZE(code),
		.filter = code,
	};

	if (setsockopt(fd, SOL_SOCKET, SO_ATTACH_REUSEPORT_CBPF, &p, sizeof(p)))
		error(1, errno, "failed to set SO_ATTACH_REUSEPORT_CBPF");
}