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
struct block_range_iter {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ block_range__next (scalar_t__) ; 

__attribute__((used)) static inline bool block_range_iter__next(struct block_range_iter *iter)
{
	if (iter->start == iter->end)
		return false;

	iter->start = block_range__next(iter->start);
	return true;
}