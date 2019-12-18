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
struct bpf_sockopt {scalar_t__ level; scalar_t__ optname; int optlen; scalar_t__ retval; int /*<<< orphan*/  sk; int /*<<< orphan*/ * optval; int /*<<< orphan*/ * optval_end; } ;
typedef  int /*<<< orphan*/  __u8 ;

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
 int /*<<< orphan*/  socket_storage_map ; 

int _getsockopt(struct bpf_sockopt *ctx)
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
		/* Not interested in SOL_SOCKET:SO_SNDBUF;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
		return 1;
	}

	if (ctx->level == SOL_TCP && ctx->optname == TCP_CONGESTION) {
		/* Not interested in SOL_TCP:TCP_CONGESTION;
		 * let next BPF program in the cgroup chain or kernel
		 * handle it.
		 */
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

	if (!ctx->retval)
		return 0; /* EPERM, kernel should not have handled
			   * SOL_CUSTOM, something is wrong!
			   */
	ctx->retval = 0; /* Reset system call return value to zero */

	optval[0] = storage->val;
	ctx->optlen = 1;

	return 1;
}