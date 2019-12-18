#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwEffects; int dwMask; scalar_t__ wWeight; int yHeight; int /*<<< orphan*/  bCharSet; int /*<<< orphan*/  bPitchAndFamily; int /*<<< orphan*/  bUnderlineType; int /*<<< orphan*/  szFaceName; } ;
struct TYPE_6__ {scalar_t__ lfWeight; int lfHeight; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfPitchAndFamily; scalar_t__ lfStrikeOut; scalar_t__ lfUnderline; scalar_t__ lfItalic; int /*<<< orphan*/  lfFaceName; } ;
typedef  TYPE_1__ LOGFONTW ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ CHARFORMAT2W ;

/* Variables and functions */
 int CFM_BOLD ; 
 int CFM_CHARSET ; 
 int CFM_FACE ; 
 int CFM_ITALIC ; 
 int CFM_SIZE ; 
 int CFM_STRIKEOUT ; 
 int CFM_UNDERLINE ; 
 int CFM_UNDERLINETYPE ; 
 int CFM_WEIGHT ; 
 int /*<<< orphan*/  CFU_UNDERLINE ; 
 scalar_t__ FW_NORMAL ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  ME_InitCharFormat2W (TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ME_CharFormatFromLogFont(HDC hDC, const LOGFONTW *lf, CHARFORMAT2W *fmt)
{
  int ry;

  ME_InitCharFormat2W(fmt);
  ry = GetDeviceCaps(hDC, LOGPIXELSY);
  lstrcpyW(fmt->szFaceName, lf->lfFaceName);
  fmt->dwEffects = 0;
  fmt->dwMask = CFM_WEIGHT|CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_UNDERLINETYPE|CFM_STRIKEOUT|CFM_SIZE|CFM_FACE|CFM_CHARSET;
  fmt->wWeight = lf->lfWeight;
  fmt->yHeight = -lf->lfHeight*1440/ry;
  if (lf->lfWeight > FW_NORMAL) fmt->dwEffects |= CFM_BOLD;
  if (lf->lfItalic) fmt->dwEffects |= CFM_ITALIC;
  if (lf->lfUnderline) fmt->dwEffects |= CFM_UNDERLINE;
  fmt->bUnderlineType = CFU_UNDERLINE;
  if (lf->lfStrikeOut) fmt->dwEffects |= CFM_STRIKEOUT;
  fmt->bPitchAndFamily = lf->lfPitchAndFamily;
  fmt->bCharSet = lf->lfCharSet;
}