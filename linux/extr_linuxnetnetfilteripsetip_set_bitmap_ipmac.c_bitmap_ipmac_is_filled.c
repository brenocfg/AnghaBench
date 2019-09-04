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
struct bitmap_ipmac_elem {scalar_t__ filled; } ;

/* Variables and functions */
 scalar_t__ MAC_FILLED ; 

__attribute__((used)) static inline int
bitmap_ipmac_is_filled(const struct bitmap_ipmac_elem *elem)
{
	return elem->filled == MAC_FILLED;
}