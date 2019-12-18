#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lfHeight; int lfItalic; int lfUnderline; int lfStrikeOut; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfPitchAndFamily; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfFaceName; } ;
struct TYPE_7__ {int dwEffects; int dwMask; scalar_t__ bUnderlineType; int /*<<< orphan*/  bCharSet; int /*<<< orphan*/  bPitchAndFamily; int /*<<< orphan*/  wWeight; int /*<<< orphan*/  yHeight; int /*<<< orphan*/  szFaceName; } ;
struct TYPE_8__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ ME_Style ;
typedef  int /*<<< orphan*/  ME_Context ;
typedef  TYPE_3__ LOGFONTW ;

/* Variables and functions */
 int CFE_LINK ; 
 int CFM_BOLD ; 
 int CFM_CHARSET ; 
 int CFM_FACE ; 
 int CFM_ITALIC ; 
 int CFM_STRIKEOUT ; 
 int CFM_SUBSCRIPT ; 
 int CFM_SUPERSCRIPT ; 
 int CFM_UNDERLINE ; 
 int CFM_WEIGHT ; 
 scalar_t__ CFU_CF1UNDERLINE ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int ME_twips2pointsY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ME_LogFontFromStyle(ME_Context* c, LOGFONTW *lf, const ME_Style *s)
{
  ZeroMemory(lf, sizeof(LOGFONTW));
  lstrcpyW(lf->lfFaceName, s->fmt.szFaceName);

  lf->lfHeight = ME_twips2pointsY(c, -s->fmt.yHeight);
  
  lf->lfWeight = FW_NORMAL;
  if (s->fmt.dwEffects & s->fmt.dwMask & CFM_BOLD)
    lf->lfWeight = FW_BOLD;
  if (s->fmt.dwMask & CFM_WEIGHT)
    lf->lfWeight = s->fmt.wWeight;
  if (s->fmt.dwEffects & s->fmt.dwMask & CFM_ITALIC)
    lf->lfItalic = 1;
  if ((s->fmt.dwEffects & s->fmt.dwMask & CFM_UNDERLINE) &&
      !(s->fmt.dwEffects & CFE_LINK) &&
      s->fmt.bUnderlineType == CFU_CF1UNDERLINE)
    lf->lfUnderline = 1;
  if (s->fmt.dwEffects & s->fmt.dwMask & CFM_STRIKEOUT)
    lf->lfStrikeOut = 1;
  if (s->fmt.dwEffects & s->fmt.dwMask & (CFM_SUBSCRIPT|CFM_SUPERSCRIPT))
    lf->lfHeight = (lf->lfHeight*2)/3;
/*lf.lfQuality = PROOF_QUALITY; */
  if (s->fmt.dwMask & CFM_FACE)
    lf->lfPitchAndFamily = s->fmt.bPitchAndFamily;
  if (s->fmt.dwMask & CFM_CHARSET)
    lf->lfCharSet = s->fmt.bCharSet;
}