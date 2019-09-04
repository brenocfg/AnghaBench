#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hwq {TYPE_1__* host_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  sq_ctx_reset; } ;

/* Variables and functions */
 int context_reset (struct hwq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int context_reset_sq(struct hwq *hwq)
{
	return context_reset(hwq, &hwq->host_map->sq_ctx_reset);
}