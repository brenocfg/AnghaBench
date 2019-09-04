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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ FUNCTION ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SortFnByName(const void *_f1, const void *_f2)
{
    const FUNCTION *f1 = _f1;
    const FUNCTION *f2 = _f2;

    if (f1->type != f2->type)
        return f1->type - f2->type;
    return strcmp(f1->name, f2->name);
}