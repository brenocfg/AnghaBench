#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ si_generation; } ;
typedef  TYPE_1__ stateid_t ;
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static inline bool nfsd4_stateid_generation_after(stateid_t *a, stateid_t *b)
{
	return (s32)(a->si_generation - b->si_generation) > 0;
}