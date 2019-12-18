#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ free_cnt; scalar_t__ alloc_cnt; int /*<<< orphan*/  (* free_fn ) (TYPE_1__*) ;struct TYPE_6__* next_node; struct TYPE_6__* mpool; } ;
typedef  TYPE_1__* HPDF_MPool_Node ;
typedef  TYPE_1__* HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PRINTF (char*,...) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

void
HPDF_MMgr_Free  (HPDF_MMgr  mmgr)
{
    HPDF_MPool_Node node;

    HPDF_PTRACE((" HPDF_MMgr_Free\n"));

    if (mmgr == NULL)
        return;

    node = mmgr->mpool;

    /* delete all nodes recursively */
    while (node != NULL) {
        HPDF_MPool_Node tmp = node;
        node = tmp->next_node;

        HPDF_PTRACE(("-%p mmgr-node-free\n", tmp));
        mmgr->free_fn (tmp);

#ifdef HPDF_MEM_DEBUG
        mmgr->free_cnt++;
#endif

    }

#ifdef HPDF_MEM_DEBUG
    HPDF_PRINTF ("# HPDF_MMgr alloc-cnt=%u, free-cnt=%u\n",
            mmgr->alloc_cnt, mmgr->free_cnt);

    if (mmgr->alloc_cnt != mmgr->free_cnt)
        HPDF_PRINTF ("# ERROR #\n");
#endif

    HPDF_PTRACE(("-%p mmgr-free\n", mmgr));
    mmgr->free_fn (mmgr);
}