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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int EFX_FARCH_FILTER_INDEX_MASK ; 

__attribute__((used)) static inline unsigned int efx_farch_filter_id_index(u32 id)
{
	return id & EFX_FARCH_FILTER_INDEX_MASK;
}