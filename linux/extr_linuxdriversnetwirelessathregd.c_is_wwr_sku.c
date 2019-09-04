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
typedef  int u16 ;

/* Variables and functions */
 int COUNTRY_ERD_FLAG ; 
 int WORLD ; 
 int WORLD_SKU_MASK ; 
 int WORLD_SKU_PREFIX ; 

__attribute__((used)) static inline bool is_wwr_sku(u16 regd)
{
	return ((regd & COUNTRY_ERD_FLAG) != COUNTRY_ERD_FLAG) &&
		(((regd & WORLD_SKU_MASK) == WORLD_SKU_PREFIX) ||
		(regd == WORLD));
}