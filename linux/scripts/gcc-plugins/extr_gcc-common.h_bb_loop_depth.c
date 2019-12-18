#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* const_basic_block ;
struct TYPE_3__ {scalar_t__ loop_father; } ;

/* Variables and functions */
 int loop_depth (scalar_t__) ; 

__attribute__((used)) static inline int bb_loop_depth(const_basic_block bb)
{
	return bb->loop_father ? loop_depth(bb->loop_father) : 0;
}