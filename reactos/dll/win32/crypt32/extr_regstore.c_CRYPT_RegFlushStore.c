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
struct TYPE_5__ {scalar_t__ dirty; } ;
typedef  TYPE_1__ WINE_REGSTOREINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_RegWriteToReg (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL CRYPT_RegFlushStore(WINE_REGSTOREINFO *store, BOOL force)
{
    BOOL ret;

    TRACE("(%p, %d)\n", store, force);

    if (store->dirty || force)
    {
        ret = CRYPT_RegWriteToReg(store);
        if (ret)
            store->dirty = FALSE;
    }
    else
        ret = TRUE;
    return ret;
}