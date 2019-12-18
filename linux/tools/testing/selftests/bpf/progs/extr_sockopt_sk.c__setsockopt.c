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
struct sockopt_sk {int /*<<< orphan*/  val; } ;
struct bpf_sockopt {scalar_t__ level; scalar_t__ optname; int optlen; int /*<<< orphan*/  sk; int /*<<< orphan*/ * optval; int /*<<< orphan*/ * optval_end; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
 scalar_t__ IP_TOS ; 
 scalar_t__ SOL_CUSTOM ; 
 scalar_t__ SOL_IP ; 
 scalar_t__ SOL_SOCKET ; 
 scalar_t__ SOL_TCP ; 
 scalar_t__ SO_SNDBUF ; 
 scalar_t__ TCP_CONGESTION ; 
 struct sockopt_sk* bpf_sk_storage_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  socket_storage_map ; 

int _setsockopt(struct bpf_sockopt *ctx)
{
	__u8 *optval_end = ctx->optval_end;
	__u8 *optval = ctx->optval;
	struct sockopt_sk *storage;

	if (ctx->level == SOL_IP && ctx->optname == IP_TOS)
		/* Not interested in SOL_IP:IP_TOS;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		return 1;

	if (ctx->level == SOL_SOCKET && ctx->optname == SO_SNDBUF) {
		/* Overwrite SO_SNDBUF value */

		if (optval + sizeof(__u32) > optval_end)
			return 0; /* EPERM, bounds check */

		*(__u32 *)optval = 0x55AA;
		ctx->optlen = 4;

		return 1;
	}

	if (ctx->level == SOL_TCP && ctx->optname == TCP_CONGESTION) {
		/* Always use cubic */

		if (optval + 5 > optval_end)
			return 0; /* EPERM, bounds check */

		memcpy(optval, "cubic", 5);
		ctx->optlen = 5;

		return 1;
	}

	if (ctx->level != SOL_CUSTOM)
		return 0; /* EPERM, deny everything except custom level */

	if (optval + 1 > optval_end)
		return 0; /* EPERM, bounds check */

	storage = bpf_sk_storage_get(&socket_storage_map, ctx->sk, 0,
				     BPF_SK_STORAGE_GET_F_CREATE);
	if (!storage)
		return 0; /* EPERM, couldn't get sk storage */

	storage->val = optval[0];
	ctx->optlen = -1; /* BPF has consumed this option, don't call kernel
			   * setsockopt handler.
			   */

	return 1;
}