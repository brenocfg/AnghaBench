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
typedef  int u64 ;
struct ring_buffer {int (* clock ) () ;} ;

/* Variables and functions */
 int DEBUG_SHIFT ; 
 int stub1 () ; 

__attribute__((used)) static inline u64 rb_time_stamp(struct ring_buffer *buffer)
{
	/* shift to debug/test normalization and TIME_EXTENTS */
	return buffer->clock() << DEBUG_SHIFT;
}