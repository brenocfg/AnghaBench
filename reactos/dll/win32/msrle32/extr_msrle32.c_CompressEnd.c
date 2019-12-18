#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nPrevFrame; int /*<<< orphan*/ * palette_map; int /*<<< orphan*/  bCompress; int /*<<< orphan*/ * pCurFrame; int /*<<< orphan*/ * pPrevFrame; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static LRESULT CompressEnd(CodecInfo *pi)
{
  TRACE("(%p)\n",pi);

  if (pi != NULL) {
    if (pi->pPrevFrame != NULL)
    {
      GlobalUnlock(GlobalHandle(pi->pPrevFrame));
      GlobalFree(GlobalHandle(pi->pPrevFrame));
    }
    if (pi->pCurFrame != NULL)
    {
      GlobalUnlock(GlobalHandle(pi->pCurFrame));
      GlobalFree(GlobalHandle(pi->pCurFrame));
    }
    pi->pPrevFrame = NULL;
    pi->pCurFrame  = NULL;
    pi->nPrevFrame = -1;
    pi->bCompress  = FALSE;

    if (pi->palette_map != NULL) {
        LocalFree(pi->palette_map);
        pi->palette_map = NULL;
    }
  }

  return ICERR_OK;
}