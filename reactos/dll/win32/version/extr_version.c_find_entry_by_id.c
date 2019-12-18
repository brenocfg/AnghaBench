#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_12__ {int NumberOfNamedEntries; int NumberOfIdEntries; } ;
struct TYPE_10__ {scalar_t__ Id; } ;
struct TYPE_8__ {int OffsetToDirectory; } ;
struct TYPE_9__ {TYPE_1__ s2; } ;
struct TYPE_11__ {TYPE_3__ u; TYPE_2__ u2; } ;
typedef  TYPE_4__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_5__ IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */

__attribute__((used)) static const IMAGE_RESOURCE_DIRECTORY *find_entry_by_id( const IMAGE_RESOURCE_DIRECTORY *dir,
                                                         WORD id, const void *root )
{
    const IMAGE_RESOURCE_DIRECTORY_ENTRY *entry;
    int min, max, pos;

    entry = (const IMAGE_RESOURCE_DIRECTORY_ENTRY *)(dir + 1);
    min = dir->NumberOfNamedEntries;
    max = min + dir->NumberOfIdEntries - 1;
    while (min <= max)
    {
        pos = (min + max) / 2;
        if (entry[pos].u.Id == id)
            return (const IMAGE_RESOURCE_DIRECTORY *)((const char *)root + entry[pos].u2.s2.OffsetToDirectory);
        if (entry[pos].u.Id > id) max = pos - 1;
        else min = pos + 1;
    }
    return NULL;
}