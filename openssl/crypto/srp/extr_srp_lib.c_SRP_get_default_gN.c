#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SRP_gN ;

/* Variables and functions */
 size_t KNOWN_GN_NUMBER ; 
 TYPE_1__* knowngN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

SRP_gN *SRP_get_default_gN(const char *id)
{
    size_t i;

    if (id == NULL)
        return knowngN;
    for (i = 0; i < KNOWN_GN_NUMBER; i++) {
        if (strcmp(knowngN[i].id, id) == 0)
            return knowngN + i;
    }
    return NULL;
}