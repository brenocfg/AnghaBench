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
struct inf_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct inf_value*) ; 

__attribute__((used)) static void inf_value_free(struct inf_value *value)
{
    heap_free(value);
}