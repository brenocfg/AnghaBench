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
struct argv {size_t argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_append (struct argv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_init (struct argv*) ; 
 int /*<<< orphan*/ * string_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct argv
argv_clone(const struct argv *a, const size_t headroom)
{
    struct argv r;
    size_t i;

    argv_init(&r);
    for (i = 0; i < headroom; ++i)
    {
        argv_append(&r, NULL);
    }
    if (a)
    {
        for (i = 0; i < a->argc; ++i)
        {
            argv_append(&r, string_alloc(a->argv[i], NULL));
        }
    }
    return r;
}