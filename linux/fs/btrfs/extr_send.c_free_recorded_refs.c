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
struct send_ctx {int /*<<< orphan*/  deleted_refs; int /*<<< orphan*/  new_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_recorded_refs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_recorded_refs(struct send_ctx *sctx)
{
	__free_recorded_refs(&sctx->new_refs);
	__free_recorded_refs(&sctx->deleted_refs);
}