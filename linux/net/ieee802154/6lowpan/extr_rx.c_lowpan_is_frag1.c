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
typedef  int u8 ;

/* Variables and functions */
 int LOWPAN_DISPATCH_FRAG1 ; 
 int LOWPAN_DISPATCH_FRAG_MASK ; 

__attribute__((used)) static inline bool lowpan_is_frag1(u8 dispatch)
{
	return (dispatch & LOWPAN_DISPATCH_FRAG_MASK) == LOWPAN_DISPATCH_FRAG1;
}