#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* script; } ;
typedef  TYPE_2__ parser_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 void* heap_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *parser_alloc_tmp(parser_ctx_t *ctx, DWORD size)
{
    return heap_pool_alloc(&ctx->script->tmp_heap, size);
}