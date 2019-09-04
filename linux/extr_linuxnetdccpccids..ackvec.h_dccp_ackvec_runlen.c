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
typedef  int const u8 ;

/* Variables and functions */
 int const DCCPAV_MAX_RUNLEN ; 

__attribute__((used)) static inline u8 dccp_ackvec_runlen(const u8 *cell)
{
	return *cell & DCCPAV_MAX_RUNLEN;
}