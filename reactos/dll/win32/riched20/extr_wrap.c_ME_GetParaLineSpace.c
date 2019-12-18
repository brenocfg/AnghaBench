#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* editor; } ;
struct TYPE_8__ {int dwMask; int bLineSpacingRule; int dyLineSpacing; } ;
struct TYPE_10__ {TYPE_1__ fmt; } ;
struct TYPE_9__ {int nZoomNumerator; int nZoomDenominator; } ;
typedef  TYPE_3__ ME_Paragraph ;
typedef  TYPE_4__ ME_Context ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int ME_twips2pointsY (TYPE_4__*,int) ; 
 int PFM_LINESPACING ; 

__attribute__((used)) static int ME_GetParaLineSpace(ME_Context* c, ME_Paragraph* para)
{
  int   sp = 0, ls = 0;
  if (!(para->fmt.dwMask & PFM_LINESPACING)) return 0;

  /* FIXME: how to compute simply the line space in ls ??? */
  /* FIXME: does line spacing include the line itself ??? */
  switch (para->fmt.bLineSpacingRule)
  {
  case 0:       sp = ls; break;
  case 1:       sp = (3 * ls) / 2; break;
  case 2:       sp = 2 * ls; break;
  case 3:       sp = ME_twips2pointsY(c, para->fmt.dyLineSpacing); if (sp < ls) sp = ls; break;
  case 4:       sp = ME_twips2pointsY(c, para->fmt.dyLineSpacing); break;
  case 5:       sp = para->fmt.dyLineSpacing / 20; break;
  default: FIXME("Unsupported spacing rule value %d\n", para->fmt.bLineSpacingRule);
  }
  if (c->editor->nZoomNumerator == 0)
    return sp;
  else
    return sp * c->editor->nZoomNumerator / c->editor->nZoomDenominator;
}