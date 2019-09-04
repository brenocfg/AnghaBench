#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashitem_T ;
struct TYPE_7__ {int /*<<< orphan*/  di_key; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ht_array; scalar_t__ ht_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASHITEM_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_5__* HI2DI (int /*<<< orphan*/ *) ; 
 scalar_t__ STRNCMP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  delete_var (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ globvarht ; 
 int /*<<< orphan*/  got_int ; 
 int /*<<< orphan*/  hash_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_unlock (TYPE_1__*) ; 

void
del_menutrans_vars()
{
    hashitem_T	*hi;
    int		todo;

    hash_lock(&globvarht);
    todo = (int)globvarht.ht_used;
    for (hi = globvarht.ht_array; todo > 0 && !got_int; ++hi)
    {
	if (!HASHITEM_EMPTY(hi))
	{
	    --todo;
	    if (STRNCMP(HI2DI(hi)->di_key, "menutrans_", 10) == 0)
		delete_var(&globvarht, hi);
	}
    }
    hash_unlock(&globvarht);
}