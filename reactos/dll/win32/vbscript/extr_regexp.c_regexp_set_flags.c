#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  source_len; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ regexp_t ;
typedef  int /*<<< orphan*/  heap_pool_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int REG_FOLD ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  regexp_destroy (TYPE_1__*) ; 
 TYPE_1__* regexp_new (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

HRESULT regexp_set_flags(regexp_t **regexp, void *cx, heap_pool_t *pool, WORD flags)
{
    if(((*regexp)->flags & REG_FOLD) != (flags & REG_FOLD)) {
        regexp_t *new_regexp = regexp_new(cx, pool, (*regexp)->source,
                (*regexp)->source_len, flags, FALSE);

        if(!new_regexp)
            return E_FAIL;

        regexp_destroy(*regexp);
        *regexp = new_regexp;
    }else {
        (*regexp)->flags = flags;
    }

    return S_OK;
}