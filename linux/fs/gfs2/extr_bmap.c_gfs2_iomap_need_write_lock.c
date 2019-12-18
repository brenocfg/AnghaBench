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

/* Variables and functions */
 unsigned int IOMAP_DIRECT ; 
 unsigned int IOMAP_WRITE ; 

__attribute__((used)) static inline bool gfs2_iomap_need_write_lock(unsigned flags)
{
	return (flags & IOMAP_WRITE) && !(flags & IOMAP_DIRECT);
}