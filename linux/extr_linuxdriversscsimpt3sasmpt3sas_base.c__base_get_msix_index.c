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
typedef  int /*<<< orphan*/  u8 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/ * cpu_msix_table; } ;

/* Variables and functions */
 size_t raw_smp_processor_id () ; 

__attribute__((used)) static inline u8
_base_get_msix_index(struct MPT3SAS_ADAPTER *ioc)
{
	return ioc->cpu_msix_table[raw_smp_processor_id()];
}