#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nCharOfs; int nFlags; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_1__ ME_Run ;

/* Variables and functions */
 int MERF_ENDWHITE ; 
 int MERF_HIDDEN ; 
 int MERF_NOTEXT ; 
 int MERF_SPLITTABLE ; 
 int MERF_STARTWHITE ; 
 int MERF_TABLESTART ; 
 int MERF_WHITESPACE ; 
 scalar_t__ ME_IsWSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ RUN_IS_HIDDEN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * get_text (TYPE_1__*,scalar_t__) ; 
 scalar_t__ run_is_entirely_ws (TYPE_1__*) ; 
 scalar_t__ run_is_splittable (TYPE_1__*) ; 

void ME_UpdateRunFlags(ME_TextEditor *editor, ME_Run *run)
{
  assert(run->nCharOfs >= 0);

  if (RUN_IS_HIDDEN(run) || run->nFlags & MERF_TABLESTART)
    run->nFlags |= MERF_HIDDEN;
  else
    run->nFlags &= ~MERF_HIDDEN;

  if (run_is_splittable( run ))
    run->nFlags |= MERF_SPLITTABLE;
  else
    run->nFlags &= ~MERF_SPLITTABLE;

  if (!(run->nFlags & MERF_NOTEXT))
  {
    if (run_is_entirely_ws( run ))
      run->nFlags |= MERF_WHITESPACE | MERF_STARTWHITE | MERF_ENDWHITE;
    else
    {
      run->nFlags &= ~MERF_WHITESPACE;

      if (ME_IsWSpace( *get_text( run, 0 ) ))
        run->nFlags |= MERF_STARTWHITE;
      else
        run->nFlags &= ~MERF_STARTWHITE;

      if (ME_IsWSpace( *get_text( run, run->len - 1 ) ))
        run->nFlags |= MERF_ENDWHITE;
      else
        run->nFlags &= ~MERF_ENDWHITE;
    }
  }
  else
    run->nFlags &= ~(MERF_WHITESPACE | MERF_STARTWHITE | MERF_ENDWHITE);
}