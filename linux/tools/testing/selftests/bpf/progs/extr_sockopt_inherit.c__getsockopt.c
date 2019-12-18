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
struct sockopt_inherit {int /*<<< orphan*/  val; } ;
struct bpf_sockopt {scalar_t__ level; int optlen; scalar_t__ retval; int /*<<< orphan*/ * optval; int /*<<< orphan*/ * optval_end; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ SOL_CUSTOM ; 
 struct sockopt_inherit* get_storage (struct bpf_sockopt*) ; 

int _getsockopt(struct bpf_sockopt *ctx)
{
	__u8 *optval_end = ctx->optval_end;
	struct sockopt_inherit *storage;
	__u8 *optval = ctx->optval;

	if (ctx->level != SOL_CUSTOM)
		return 1; /* only interested in SOL_CUSTOM */

	if (optval + 1 > optval_end)
		return 0; /* EPERM, bounds check */

	storage = get_storage(ctx);
	if (!storage)
		return 0; /* EPERM, couldn't get sk storage */

	ctx->retval = 0; /* Reset system call return value to zero */

	optval[0] = storage->val;
	ctx->optlen = 1;

	return 1;
}