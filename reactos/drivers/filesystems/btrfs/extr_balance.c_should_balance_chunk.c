#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint16_t ;
struct TYPE_10__ {TYPE_5__* opts; } ;
struct TYPE_12__ {TYPE_1__ balance; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_13__ {scalar_t__ offset; int used; TYPE_2__* chunk_item; } ;
typedef  TYPE_4__ chunk ;
struct TYPE_14__ {int flags; scalar_t__ profiles; scalar_t__ devid; scalar_t__ drange_end; scalar_t__ drange_start; scalar_t__ vrange_start; scalar_t__ vrange_end; scalar_t__ stripes_start; scalar_t__ stripes_end; scalar_t__ usage_start; scalar_t__ usage_end; scalar_t__ convert; } ;
typedef  TYPE_5__ btrfs_balance_opts ;
struct TYPE_15__ {scalar_t__ dev_id; scalar_t__ offset; } ;
struct TYPE_11__ {size_t num_stripes; int type; size_t sub_stripes; size_t size; } ;
typedef  TYPE_6__ CHUNK_ITEM_STRIPE ;

/* Variables and functions */
 int BLOCK_FLAG_RAID0 ; 
 int BLOCK_FLAG_RAID10 ; 
 int BLOCK_FLAG_RAID5 ; 
 int BLOCK_FLAG_RAID6 ; 
 int BTRFS_BALANCE_OPTS_CONVERT ; 
 int BTRFS_BALANCE_OPTS_DEVID ; 
 int BTRFS_BALANCE_OPTS_DRANGE ; 
 int BTRFS_BALANCE_OPTS_ENABLED ; 
 int BTRFS_BALANCE_OPTS_PROFILES ; 
 int BTRFS_BALANCE_OPTS_SOFT ; 
 int BTRFS_BALANCE_OPTS_STRIPES ; 
 int BTRFS_BALANCE_OPTS_USAGE ; 
 int BTRFS_BALANCE_OPTS_VRANGE ; 
 scalar_t__ get_chunk_dup_type (TYPE_4__*) ; 

__attribute__((used)) static bool should_balance_chunk(device_extension* Vcb, uint8_t sort, chunk* c) {
    btrfs_balance_opts* opts;

    opts = &Vcb->balance.opts[sort];

    if (!(opts->flags & BTRFS_BALANCE_OPTS_ENABLED))
        return false;

    if (opts->flags & BTRFS_BALANCE_OPTS_PROFILES) {
        uint64_t type = get_chunk_dup_type(c);

        if (!(type & opts->profiles))
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_DEVID) {
        uint16_t i;
        CHUNK_ITEM_STRIPE* cis = (CHUNK_ITEM_STRIPE*)&c->chunk_item[1];
        bool b = false;

        for (i = 0; i < c->chunk_item->num_stripes; i++) {
            if (cis[i].dev_id == opts->devid) {
                b = true;
                break;
            }
        }

        if (!b)
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_DRANGE) {
        uint16_t i, factor;
        uint64_t physsize;
        CHUNK_ITEM_STRIPE* cis = (CHUNK_ITEM_STRIPE*)&c->chunk_item[1];
        bool b = false;

        if (c->chunk_item->type & BLOCK_FLAG_RAID0)
            factor = c->chunk_item->num_stripes;
        else if (c->chunk_item->type & BLOCK_FLAG_RAID10)
            factor = c->chunk_item->num_stripes / c->chunk_item->sub_stripes;
        else if (c->chunk_item->type & BLOCK_FLAG_RAID5)
            factor = c->chunk_item->num_stripes - 1;
        else if (c->chunk_item->type & BLOCK_FLAG_RAID6)
            factor = c->chunk_item->num_stripes - 2;
        else // SINGLE, DUPLICATE, RAID1
            factor = 1;

        physsize = c->chunk_item->size / factor;

        for (i = 0; i < c->chunk_item->num_stripes; i++) {
            if (cis[i].offset < opts->drange_end && cis[i].offset + physsize >= opts->drange_start &&
                (!(opts->flags & BTRFS_BALANCE_OPTS_DEVID) || cis[i].dev_id == opts->devid)) {
                b = true;
                break;
            }
        }

        if (!b)
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_VRANGE) {
        if (c->offset + c->chunk_item->size <= opts->vrange_start || c->offset > opts->vrange_end)
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_STRIPES) {
        if (c->chunk_item->num_stripes < opts->stripes_start || c->chunk_item->num_stripes < opts->stripes_end)
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_USAGE) {
        uint64_t usage = c->used * 100 / c->chunk_item->size;

        // usage == 0 should mean completely empty, not just that usage rounds to 0%
        if (c->used > 0 && usage == 0)
            usage = 1;

        if (usage < opts->usage_start || usage > opts->usage_end)
            return false;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_CONVERT && opts->flags & BTRFS_BALANCE_OPTS_SOFT) {
        uint64_t type = get_chunk_dup_type(c);

        if (type == opts->convert)
            return false;
    }

    return true;
}