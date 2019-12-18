#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_entry {int dummy; } ;
struct TYPE_5__ {scalar_t__ superblock; scalar_t__ fileid; } ;
typedef  TYPE_2__ nfs41_fh ;
struct TYPE_4__ {TYPE_2__ fh; } ;
struct TYPE_6__ {TYPE_1__ file; } ;

/* Variables and functions */
 TYPE_3__* deleg_entry (struct list_entry const*) ; 

__attribute__((used)) static int deleg_file_cmp(const struct list_entry *entry, const void *value)
{
    const nfs41_fh *lhs = &deleg_entry(entry)->file.fh;
    const nfs41_fh *rhs = (const nfs41_fh*)value;
    if (lhs->superblock != rhs->superblock) return -1;
    if (lhs->fileid != rhs->fileid) return -1;
    return 0;
}