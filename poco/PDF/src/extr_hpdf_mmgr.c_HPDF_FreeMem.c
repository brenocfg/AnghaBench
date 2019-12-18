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
struct TYPE_3__ {int /*<<< orphan*/  free_cnt; int /*<<< orphan*/  (* free_fn ) (void*) ;int /*<<< orphan*/  mpool; } ;
typedef  TYPE_1__* HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
HPDF_FreeMem  (HPDF_MMgr  mmgr,
               void       *aptr)
{
    if (!aptr)
        return;

    if (!mmgr->mpool) {
        HPDF_PTRACE(("-%p mmgr-free-mem\n", aptr));
        mmgr->free_fn(aptr);

#ifdef HPDF_MEM_DEBUG
        mmgr->free_cnt++;
#endif
    }

    return;
}