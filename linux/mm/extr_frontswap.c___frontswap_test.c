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
struct swap_info_struct {scalar_t__ frontswap_map; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int test_bit (int /*<<< orphan*/ ,scalar_t__) ; 

bool __frontswap_test(struct swap_info_struct *sis,
				pgoff_t offset)
{
	if (sis->frontswap_map)
		return test_bit(offset, sis->frontswap_map);
	return false;
}