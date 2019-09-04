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
struct sock_fprog {unsigned int len; struct sock_filter* filter; } ;
struct sock_filter {scalar_t__ k; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  bpf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ SKF_AD_OFF ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ATTACH_FILTER ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  rl_printf (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_fprog*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bpf_runnable(struct sock_filter *f, unsigned int len)
{
	int sock, ret, i;
	struct sock_fprog bpf = {
		.filter = f,
		.len = len,
	};

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		rl_printf("cannot open socket!\n");
		return false;
	}
	ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
	close(sock);
	if (ret < 0) {
		rl_printf("program not allowed to run by kernel!\n");
		return false;
	}
	for (i = 0; i < len; i++) {
		if (BPF_CLASS(f[i].code) == BPF_LD &&
		    f[i].k > SKF_AD_OFF) {
			rl_printf("extensions currently not supported!\n");
			return false;
		}
	}

	return true;
}