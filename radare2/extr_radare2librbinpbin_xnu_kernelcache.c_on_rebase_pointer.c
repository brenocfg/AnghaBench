#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
struct TYPE_5__ {scalar_t__ off; scalar_t__ eob; scalar_t__ count; int /*<<< orphan*/ * buf; int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ RRebaseCtx ;
typedef  TYPE_2__ RParsedPointer ;

/* Variables and functions */
 int /*<<< orphan*/  r_parse_pointer (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_write_le64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool on_rebase_pointer (ut64 offset, ut64 decorated_addr, RRebaseCtx *ctx) {
	if (offset < ctx->off) {
		return true;
	}
	if (offset >= ctx->eob) {
		return false;
	}
	ut64 in_buf = offset - ctx->off;
	if (in_buf >= ctx->count || (in_buf + 8) > ctx->count) {
		return false;
	}

	RParsedPointer ptr;
	r_parse_pointer (&ptr, decorated_addr, ctx->obj);

	r_write_le64 (&ctx->buf[in_buf], ptr.address);

	return true;
}