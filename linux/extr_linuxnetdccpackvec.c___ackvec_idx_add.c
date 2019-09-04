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
typedef  int const u16 ;

/* Variables and functions */
 int const DCCPAV_MAX_ACKVEC_LEN ; 

__attribute__((used)) static inline u16 __ackvec_idx_add(const u16 a, const u16 b)
{
	return (a + b) % DCCPAV_MAX_ACKVEC_LEN;
}