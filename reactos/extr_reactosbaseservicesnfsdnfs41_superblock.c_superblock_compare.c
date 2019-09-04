#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fsid; } ;
typedef  TYPE_1__ nfs41_superblock ;
typedef  int /*<<< orphan*/  nfs41_fsid ;

/* Variables and functions */
 int compare_fsid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_1__* superblock_entry (struct list_entry const*) ; 

__attribute__((used)) static int superblock_compare(
    const struct list_entry *entry,
    const void *value)
{
    const nfs41_superblock *superblock = superblock_entry(entry);
    return compare_fsid(&superblock->fsid, (const nfs41_fsid*)value);
}