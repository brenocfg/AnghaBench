#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_24__ {scalar_t__ fRTL; } ;
struct TYPE_23__ {TYPE_2__* editor; } ;
struct TYPE_22__ {int nFlags; int nWidth; int /*<<< orphan*/  style; int /*<<< orphan*/  len; TYPE_8__ script_analysis; int /*<<< orphan*/  advances; int /*<<< orphan*/  vis_attrs; int /*<<< orphan*/  clusters; int /*<<< orphan*/  num_glyphs; TYPE_1__* para; } ;
struct TYPE_21__ {int /*<<< orphan*/ * szData; } ;
struct TYPE_20__ {int cx; } ;
struct TYPE_19__ {scalar_t__ cPasswordMask; } ;
struct TYPE_18__ {int nFlags; } ;
typedef  TYPE_3__ SIZE ;
typedef  TYPE_4__ ME_String ;
typedef  TYPE_5__ ME_Run ;
typedef  TYPE_6__ ME_Context ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MEPF_COMPLEX ; 
 int MERF_ENDPARA ; 
 int MERF_GRAPHICS ; 
 int /*<<< orphan*/  ME_DestroyString (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_GetOLEObjectSize (TYPE_6__*,TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ME_GetTextExtent (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_4__* ME_MakeStringR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptCPtoX (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int*) ; 
 int /*<<< orphan*/ * get_text (TYPE_5__*,int /*<<< orphan*/ ) ; 

int ME_PointFromCharContext(ME_Context *c, ME_Run *pRun, int nOffset, BOOL visual_order)
{
  SIZE size;
  ME_String *mask_text = NULL;
  WCHAR *str;

  if (pRun->nFlags & MERF_GRAPHICS)
  {
    if (nOffset)
      ME_GetOLEObjectSize(c, pRun, &size);
    return nOffset != 0;
  } else if (pRun->nFlags & MERF_ENDPARA) {
    nOffset = 0;
  }

  if (pRun->para->nFlags & MEPF_COMPLEX)
  {
      int x;
      ScriptCPtoX( nOffset, FALSE, pRun->len, pRun->num_glyphs, pRun->clusters,
                   pRun->vis_attrs, pRun->advances, &pRun->script_analysis, &x );
      if (visual_order && pRun->script_analysis.fRTL) x = pRun->nWidth - x - 1;
      return x;
  }
  if (c->editor->cPasswordMask)
  {
    mask_text = ME_MakeStringR(c->editor->cPasswordMask, pRun->len);
    str = mask_text->szData;
  }
  else
      str = get_text( pRun, 0 );

  ME_GetTextExtent(c, str, nOffset, pRun->style, &size);
  ME_DestroyString( mask_text );
  return size.cx;
}