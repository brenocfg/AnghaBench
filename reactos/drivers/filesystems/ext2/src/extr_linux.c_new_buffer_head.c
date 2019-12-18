#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int /*<<< orphan*/  b_ts_creat; int /*<<< orphan*/  b_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  bh_acount; int /*<<< orphan*/  bh_count; int /*<<< orphan*/  bh_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_BH ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INC_MEM_COUNT (int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PS_BUFF_HEAD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ g_jbh ; 
 struct buffer_head* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct buffer_head*,int /*<<< orphan*/ ,int) ; 

struct buffer_head *
new_buffer_head()
{
    struct buffer_head * bh = NULL;
    bh = kmem_cache_alloc(g_jbh.bh_cache, GFP_NOFS);
    if (bh) {
        atomic_inc(&g_jbh.bh_count);
        atomic_inc(&g_jbh.bh_acount);

        memset(bh, 0, sizeof(struct buffer_head));
        InitializeListHead(&bh->b_link);
        KeQuerySystemTime(&bh->b_ts_creat);
        DEBUG(DL_BH, ("bh=%p allocated.\n", bh));
        INC_MEM_COUNT(PS_BUFF_HEAD, bh, sizeof(struct buffer_head));
    }

    return bh;
}