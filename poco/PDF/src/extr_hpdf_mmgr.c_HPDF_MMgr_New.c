#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* buf_size; scalar_t__ alloc_cnt; TYPE_1__* mpool; int /*<<< orphan*/  (* free_fn ) (TYPE_2__*) ;scalar_t__ (* alloc_fn ) (void*) ;scalar_t__ free_cnt; int /*<<< orphan*/  error; } ;
struct TYPE_8__ {int /*<<< orphan*/ * next_node; scalar_t__ used_size; void* size; int /*<<< orphan*/ * buf; } ;
typedef  void* HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_MPool_Node_Rec ;
typedef  TYPE_1__* HPDF_MPool_Node ;
typedef  int /*<<< orphan*/  HPDF_MMgr_Rec ;
typedef  TYPE_2__* HPDF_MMgr ;
typedef  int /*<<< orphan*/  (* HPDF_Free_Func ) (TYPE_2__*) ;
typedef  int /*<<< orphan*/  HPDF_Error ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  scalar_t__ (* HPDF_Alloc_Func ) (int) ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FAILD_TO_ALLOC_MEM ; 
 int /*<<< orphan*/  HPDF_NOERROR ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternalFreeMem (TYPE_2__*) ; 
 scalar_t__ InternalGetMem (int) ; 
 scalar_t__ stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

HPDF_MMgr
HPDF_MMgr_New  (HPDF_Error       error,
                HPDF_UINT        buf_size,
                HPDF_Alloc_Func  alloc_fn,
                HPDF_Free_Func   free_fn)
{
    HPDF_MMgr mmgr;

    HPDF_PTRACE((" HPDF_MMgr_New\n"));

    if (alloc_fn)
        mmgr = (HPDF_MMgr)alloc_fn (sizeof(HPDF_MMgr_Rec));
    else
        mmgr = (HPDF_MMgr)InternalGetMem (sizeof(HPDF_MMgr_Rec));

    HPDF_PTRACE(("+%p mmgr-new\n", mmgr));

    if (mmgr != NULL) {
        /* initialize mmgr object */
        mmgr->error = error;


#ifdef HPDF_MEM_DEBUG
        mmgr->alloc_cnt = 0;
        mmgr->free_cnt = 0;
#endif
        /*
         *  if alloc_fn and free_fn are specified, these function is
         *  used. if not, default function (maybe these will be "malloc" and
         *  "free") is used.
         */
        if (alloc_fn && free_fn) {
            mmgr->alloc_fn = alloc_fn;
            mmgr->free_fn = free_fn;
        } else {
            mmgr->alloc_fn = InternalGetMem;
            mmgr->free_fn = InternalFreeMem;
        }

        /*
         *  if buf_size parameter is specified, this object is configured
         *  to be using memory-pool.
         *
         */
        if (!buf_size)
            mmgr->mpool = NULL;
        else {
            HPDF_MPool_Node node;

            node = (HPDF_MPool_Node)mmgr->alloc_fn (sizeof(HPDF_MPool_Node_Rec) +
                    buf_size);

            HPDF_PTRACE(("+%p mmgr-node-new\n", node));

            if (node == NULL) {
                HPDF_SetError (error, HPDF_FAILD_TO_ALLOC_MEM, HPDF_NOERROR);

                mmgr->free_fn(mmgr);
                mmgr = NULL;
            } else {
                mmgr->mpool = node;
                node->buf = (HPDF_BYTE *)node + sizeof(HPDF_MPool_Node_Rec);
                node->size = buf_size;
                node->used_size = 0;
                node->next_node = NULL;
            }

#ifdef HPDF_MEM_DEBUG
            if (mmgr) {
                mmgr->alloc_cnt += 1;
            }
#endif
        }

        if (mmgr) {
            mmgr->buf_size = buf_size;
        }
    } else
        HPDF_SetError(error, HPDF_FAILD_TO_ALLOC_MEM, HPDF_NOERROR);

    return mmgr;
}