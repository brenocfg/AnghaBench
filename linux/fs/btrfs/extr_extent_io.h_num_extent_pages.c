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
struct extent_buffer {int start; scalar_t__ len; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int round_up (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int num_extent_pages(const struct extent_buffer *eb)
{
	return (round_up(eb->start + eb->len, PAGE_SIZE) >> PAGE_SHIFT) -
	       (eb->start >> PAGE_SHIFT);
}