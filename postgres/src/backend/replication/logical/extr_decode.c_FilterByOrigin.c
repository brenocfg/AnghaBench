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
struct TYPE_5__ {int /*<<< orphan*/ * filter_by_origin_cb; } ;
struct TYPE_6__ {TYPE_1__ callbacks; } ;
typedef  int /*<<< orphan*/  RepOriginId ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int filter_by_origin_cb_wrapper (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
FilterByOrigin(LogicalDecodingContext *ctx, RepOriginId origin_id)
{
	if (ctx->callbacks.filter_by_origin_cb == NULL)
		return false;

	return filter_by_origin_cb_wrapper(ctx, origin_id);
}