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
struct sparsebit {int /*<<< orphan*/  num_set; } ;
typedef  int /*<<< orphan*/  sparsebit_num_t ;

/* Variables and functions */

sparsebit_num_t sparsebit_num_set(struct sparsebit *s)
{
	return s->num_set;
}