#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* Free ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ CSeqInFilter ;

/* Variables and functions */
 TYPE_2__ g_Alloc ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SeqInFilter_Free(CSeqInFilter *p)
{
  if (p->buf)
  {
    g_Alloc.Free(&g_Alloc, p->buf);
    p->buf = NULL;
  }
}