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
struct TYPE_3__ {int num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* trace_categories ; 

int OSSL_trace_get_category_num(const char *name)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(trace_categories); i++)
        if (strcasecmp(name, trace_categories[i].name) == 0)
            return trace_categories[i].num;
    return -1; /* not found */
}