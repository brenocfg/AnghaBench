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
typedef  int uint32_t ;

/* Variables and functions */
 int OVS_UFID_F_OMIT_MASK ; 

__attribute__((used)) static bool should_fill_mask(uint32_t ufid_flags)
{
	return !(ufid_flags & OVS_UFID_F_OMIT_MASK);
}