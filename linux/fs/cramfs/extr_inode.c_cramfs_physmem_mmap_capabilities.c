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
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int NOMMU_MAP_COPY ; 
 unsigned int NOMMU_MAP_DIRECT ; 
 unsigned int NOMMU_MAP_EXEC ; 
 unsigned int NOMMU_MAP_READ ; 

__attribute__((used)) static unsigned int cramfs_physmem_mmap_capabilities(struct file *file)
{
	return NOMMU_MAP_COPY | NOMMU_MAP_DIRECT |
	       NOMMU_MAP_READ | NOMMU_MAP_EXEC;
}