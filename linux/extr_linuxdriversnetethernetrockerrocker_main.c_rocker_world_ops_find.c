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
typedef  scalar_t__ u8 ;
struct rocker_world_ops {scalar_t__ mode; } ;

/* Variables and functions */
 int ROCKER_WORLD_OPS_LEN ; 
 struct rocker_world_ops** rocker_world_ops ; 

__attribute__((used)) static struct rocker_world_ops *rocker_world_ops_find(u8 mode)
{
	int i;

	for (i = 0; i < ROCKER_WORLD_OPS_LEN; i++)
		if (rocker_world_ops[i]->mode == mode)
			return rocker_world_ops[i];
	return NULL;
}