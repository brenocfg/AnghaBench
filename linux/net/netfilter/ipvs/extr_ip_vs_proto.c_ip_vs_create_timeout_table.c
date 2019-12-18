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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* kmemdup (int*,int,int /*<<< orphan*/ ) ; 

int *
ip_vs_create_timeout_table(int *table, int size)
{
	return kmemdup(table, size, GFP_KERNEL);
}