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
struct TYPE_3__ {int mask; int /*<<< orphan*/  name; } ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_1__* cfflags ; 

__attribute__((used)) static void _dump_cf_flags(DWORD cflags)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(cfflags); i++)
        if (cfflags[i].mask & cflags)
            TRACE("%s|",cfflags[i].name);
    TRACE("\n");
}