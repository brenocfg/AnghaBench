#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num; TYPE_1__* array; } ;
struct ep_struct {TYPE_2__ vars; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ep_struct_mapped(struct ep_struct *eps)
{
	if (eps->vars.num > 0)
		return eps->vars.array[0].mapping != NULL;

	return false;
}