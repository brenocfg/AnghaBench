#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hash_table_off; } ;
typedef  TYPE_2__ urlcache_header ;
struct TYPE_8__ {scalar_t__ signature; } ;
struct TYPE_10__ {scalar_t__ id; TYPE_1__ header; int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ entry_hash_table ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HASH_SIGNATURE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* urlcache_get_hash_table (TYPE_2__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL urlcache_enum_hash_tables(const urlcache_header *pHeader, DWORD *id, entry_hash_table **ppHashEntry)
{
    for (*ppHashEntry = urlcache_get_hash_table(pHeader, pHeader->hash_table_off);
         *ppHashEntry; *ppHashEntry = urlcache_get_hash_table(pHeader, (*ppHashEntry)->next))
    {
        TRACE("looking at hash table number %d\n", (*ppHashEntry)->id);
        if ((*ppHashEntry)->id != *id)
            continue;
        /* make sure that it is in fact a hash entry */
        if ((*ppHashEntry)->header.signature != HASH_SIGNATURE)
        {
            ERR("Error: not right signature (\"%.4s\") - expected \"HASH\"\n", (LPCSTR)&(*ppHashEntry)->header.signature);
            (*id)++;
            continue;
        }

        TRACE("hash table number %d found\n", *id);
        return TRUE;
    }
    return FALSE;
}