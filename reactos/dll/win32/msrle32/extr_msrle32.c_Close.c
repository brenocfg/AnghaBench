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
struct TYPE_6__ {int /*<<< orphan*/ * pCurFrame; int /*<<< orphan*/ * pPrevFrame; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CompressEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT Close(CodecInfo *pi)
{
  TRACE("(%p)\n", pi);

  /* pre-condition */
  assert(pi != NULL);

  if (pi->pPrevFrame != NULL || pi->pCurFrame != NULL)
    CompressEnd(pi);

  LocalFree(pi);
  return 1;
}