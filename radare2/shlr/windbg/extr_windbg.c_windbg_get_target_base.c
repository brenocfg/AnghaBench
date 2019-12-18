#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int is_x64; TYPE_1__* target; int /*<<< orphan*/  syncd; int /*<<< orphan*/  io_ptr; } ;
typedef  TYPE_2__ WindCtx ;
struct TYPE_6__ {int /*<<< orphan*/  peb; } ;

/* Variables and functions */
 scalar_t__ O_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_ImageBaseAddress ; 
 int /*<<< orphan*/  windbg_read_at_phys (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  windbg_va_to_pa (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 

ut64 windbg_get_target_base(WindCtx *ctx) {
	ut64 ppeb;
	ut64 base = 0;

	if (!ctx || !ctx->io_ptr || !ctx->syncd || !ctx->target) {
		return 0;
	}

	if (!windbg_va_to_pa (ctx, ctx->target->peb, &ppeb)) {
		return 0;
	}

	if (!windbg_read_at_phys (ctx, (uint8_t *) &base,
		    ppeb + O_(P_ImageBaseAddress), 4 << ctx->is_x64)) {
		return 0;
	}

	return base;
}