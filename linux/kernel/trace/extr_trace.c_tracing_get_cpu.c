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
struct inode {scalar_t__ i_cdev; } ;

/* Variables and functions */
 int RING_BUFFER_ALL_CPUS ; 

__attribute__((used)) static inline int tracing_get_cpu(struct inode *inode)
{
	if (inode->i_cdev) /* See trace_create_cpu_file() */
		return (long)inode->i_cdev - 1;
	return RING_BUFFER_ALL_CPUS;
}