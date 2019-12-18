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
struct dentry {void* d_fsdata; } ;

/* Variables and functions */
 int HZ ; 
 int jiffies ; 
 int orangefs_dcache_timeout_msecs ; 

__attribute__((used)) static inline void orangefs_set_timeout(struct dentry *dentry)
{
	unsigned long time = jiffies + orangefs_dcache_timeout_msecs*HZ/1000;

	dentry->d_fsdata = (void *) time;
}