#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cache_size; scalar_t__ pos; scalar_t__ count; scalar_t__ cache; int /*<<< orphan*/  range; scalar_t__ low; } ;
typedef  TYPE_1__ lzma_range_encoder ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 

__attribute__((used)) static inline void
rc_reset(lzma_range_encoder *rc)
{
	rc->low = 0;
	rc->cache_size = 1;
	rc->range = UINT32_MAX;
	rc->cache = 0;
	rc->count = 0;
	rc->pos = 0;
}