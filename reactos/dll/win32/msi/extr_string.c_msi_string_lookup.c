#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t maxcount; TYPE_1__* strings; } ;
typedef  TYPE_2__ string_table ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_4__ {int len; int /*<<< orphan*/  const* data; int /*<<< orphan*/  nonpersistent_refcount; int /*<<< orphan*/  persistent_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* szEmpty ; 

const WCHAR *msi_string_lookup( const string_table *st, UINT id, int *len )
{
    if( id == 0 )
    {
        if (len) *len = 0;
        return szEmpty;
    }
    if( id >= st->maxcount )
        return NULL;

    if( id && !st->strings[id].persistent_refcount && !st->strings[id].nonpersistent_refcount)
        return NULL;

    if (len) *len = st->strings[id].len;

    return st->strings[id].data;
}