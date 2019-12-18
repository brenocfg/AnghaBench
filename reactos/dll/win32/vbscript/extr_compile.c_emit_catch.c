#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  instr_cnt; } ;
typedef  TYPE_1__ compile_ctx_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  emit_catch_jmp (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL emit_catch(compile_ctx_t *ctx, unsigned off)
{
    return emit_catch_jmp(ctx, off, ctx->instr_cnt);
}