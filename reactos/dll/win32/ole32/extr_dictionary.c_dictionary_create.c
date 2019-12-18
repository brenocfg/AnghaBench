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
struct dictionary {scalar_t__ num_entries; int /*<<< orphan*/ * head; void* extra; int /*<<< orphan*/  destroy; scalar_t__ comp; } ;
typedef  int /*<<< orphan*/  destroyfunc ;
typedef  scalar_t__ comparefunc ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct dictionary* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,struct dictionary*,...) ; 

struct dictionary *dictionary_create(comparefunc c, destroyfunc d, void *extra)
{
    struct dictionary *ret;

    TRACE("(%p, %p, %p)\n", c, d, extra);
    if (!c)
        return NULL;
    ret = HeapAlloc(GetProcessHeap(), 0, sizeof(struct dictionary));
    if (ret)
    {
        ret->comp = c;
        ret->destroy = d;
        ret->extra = extra;
        ret->head = NULL;
        ret->num_entries = 0;
    }
    TRACE("returning %p\n", ret);
    return ret;
}