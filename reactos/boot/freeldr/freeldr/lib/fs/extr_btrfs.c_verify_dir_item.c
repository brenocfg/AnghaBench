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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct btrfs_dir_item {scalar_t__ type; int name_len; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTRFS_FT_MAX ; 
 scalar_t__ BTRFS_FT_XATTR ; 
 int BTRFS_NAME_MAX ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN verify_dir_item(struct btrfs_dir_item *item, u32 start, u32 total)
{
    u16 max_len = BTRFS_NAME_MAX;
    u32 end;

    if (item->type >= BTRFS_FT_MAX)
    {
        ERR("Invalid dir item type: %i\n", item->type);
        return TRUE;
    }

    if (item->type == BTRFS_FT_XATTR)
        max_len = 255; /* XATTR_NAME_MAX */

    end = start + sizeof(*item) + item->name_len;
    if (item->name_len > max_len || end > total)
    {
        ERR("Invalid dir item name len: %u\n", item->name_len);
        return TRUE;
    }

    return FALSE;
}