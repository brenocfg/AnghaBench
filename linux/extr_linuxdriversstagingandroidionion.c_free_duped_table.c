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
struct sg_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 

__attribute__((used)) static void free_duped_table(struct sg_table *table)
{
	sg_free_table(table);
	kfree(table);
}