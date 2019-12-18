#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_name; } ;
typedef  int /*<<< orphan*/  AVal ;
typedef  TYPE_1__ AMFObjectProperty ;

/* Variables and functions */

void
AMFProp_SetName(AMFObjectProperty *prop, AVal *name)
{
    prop->p_name = *name;
}