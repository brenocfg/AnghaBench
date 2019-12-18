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
 int get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readdir_map ; 

int orangefs_readdir_index_get(void)
{
	return get(&readdir_map);
}