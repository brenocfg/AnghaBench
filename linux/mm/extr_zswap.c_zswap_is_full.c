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

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int totalram_pages () ; 
 int zswap_max_pool_percent ; 
 int /*<<< orphan*/  zswap_pool_total_size ; 

__attribute__((used)) static bool zswap_is_full(void)
{
	return totalram_pages() * zswap_max_pool_percent / 100 <
			DIV_ROUND_UP(zswap_pool_total_size, PAGE_SIZE);
}