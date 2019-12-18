#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct options {int /*<<< orphan*/  ce; TYPE_1__* connection_list; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ ** array; } ;

/* Variables and functions */
 int /*<<< orphan*/  options_postprocess_verify_ce (struct options const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
options_postprocess_verify(const struct options *o)
{
    if (o->connection_list)
    {
        int i;
        for (i = 0; i < o->connection_list->len; ++i)
        {
            options_postprocess_verify_ce(o, o->connection_list->array[i]);
        }
    }
    else
    {
        options_postprocess_verify_ce(o, &o->ce);
    }
}