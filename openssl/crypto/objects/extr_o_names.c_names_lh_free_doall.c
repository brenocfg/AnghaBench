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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_NAME_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ free_type ; 

__attribute__((used)) static void names_lh_free_doall(OBJ_NAME *onp)
{
    if (onp == NULL)
        return;

    if (free_type < 0 || free_type == onp->type)
        OBJ_NAME_remove(onp->name, onp->type);
}