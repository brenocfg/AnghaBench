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
struct TYPE_3__ {size_t const full; } ;
typedef  TYPE_1__ lzma_dict ;

/* Variables and functions */

__attribute__((used)) static inline bool
dict_is_distance_valid(const lzma_dict *const dict, const size_t distance)
{
	return dict->full > distance;
}