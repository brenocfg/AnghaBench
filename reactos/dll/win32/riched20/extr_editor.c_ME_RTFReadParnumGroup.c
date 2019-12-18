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
typedef  void* WORD ;
typedef  char WCHAR ;
struct TYPE_8__ {int dwMask; int wNumbering; void* wNumberingTab; int /*<<< orphan*/  wNumberingStyle; void* wNumberingStart; } ;
struct TYPE_9__ {int rtfMinor; scalar_t__ rtfClass; char rtfMajor; TYPE_1__ fmt; void* rtfParam; } ;
typedef  TYPE_2__ RTF_Info ;

/* Variables and functions */
 int PFM_NUMBERING ; 
 int PFM_NUMBERINGSTART ; 
 int PFM_NUMBERINGSTYLE ; 
 int PFM_NUMBERINGTAB ; 
 int /*<<< orphan*/  PFNS_PAREN ; 
 int /*<<< orphan*/  PFNS_PARENS ; 
 int /*<<< orphan*/  PFNS_PERIOD ; 
 int /*<<< orphan*/  PFNS_PLAIN ; 
 int PFN_ARABIC ; 
 int PFN_BULLET ; 
 int PFN_LCLETTER ; 
 int PFN_LCROMAN ; 
 int PFN_UCLETTER ; 
 int PFN_UCROMAN ; 
 scalar_t__ RTFCheckCM (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RTFCheckCMM (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTFGetToken (TYPE_2__*) ; 
 int /*<<< orphan*/  RTFRouteToken (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,int,void*,void*,char,char) ; 
 int /*<<< orphan*/  rtfBeginGroup ; 
 int /*<<< orphan*/  rtfControl ; 
 int /*<<< orphan*/  rtfDestination ; 
 scalar_t__ rtfEOF ; 
 int /*<<< orphan*/  rtfEndGroup ; 
 int /*<<< orphan*/  rtfGroup ; 
 int /*<<< orphan*/  rtfParAttr ; 
#define  rtfParBullet 137 
#define  rtfParLevel 136 
#define  rtfParNumDecimal 135 
#define  rtfParNumIndent 134 
#define  rtfParNumLLetter 133 
#define  rtfParNumLRoman 132 
#define  rtfParNumStartAt 131 
 int rtfParNumTextAfter ; 
 int rtfParNumTextBefore ; 
#define  rtfParNumULetter 130 
#define  rtfParNumURoman 129 
#define  rtfParSimple 128 
 scalar_t__ rtfText ; 

__attribute__((used)) static void ME_RTFReadParnumGroup( RTF_Info *info )
{
    int level = 1, type = -1;
    WORD indent = 0, start = 1;
    WCHAR txt_before = 0, txt_after = 0;

    for (;;)
    {
        RTFGetToken( info );

        if (RTFCheckCMM( info, rtfControl, rtfDestination, rtfParNumTextBefore ) ||
            RTFCheckCMM( info, rtfControl, rtfDestination, rtfParNumTextAfter ))
        {
            int loc = info->rtfMinor;

            RTFGetToken( info );
            if (info->rtfClass == rtfText)
            {
                if (loc == rtfParNumTextBefore)
                    txt_before = info->rtfMajor;
                else
                    txt_after = info->rtfMajor;
                continue;
            }
            /* falling through to catch EOFs and group level changes */
        }

        if (info->rtfClass == rtfEOF)
            return;

        if (RTFCheckCM( info, rtfGroup, rtfEndGroup ))
        {
            if (--level == 0) break;
            continue;
        }

        if (RTFCheckCM( info, rtfGroup, rtfBeginGroup ))
        {
            level++;
            continue;
        }

        /* Ignore non para-attr */
        if (!RTFCheckCM( info, rtfControl, rtfParAttr ))
            continue;

        switch (info->rtfMinor)
        {
        case rtfParLevel: /* Para level is ignored */
        case rtfParSimple:
            break;
        case rtfParBullet:
            type = PFN_BULLET;
            break;

        case rtfParNumDecimal:
            type = PFN_ARABIC;
            break;
        case rtfParNumULetter:
            type = PFN_UCLETTER;
            break;
        case rtfParNumURoman:
            type = PFN_UCROMAN;
            break;
        case rtfParNumLLetter:
            type = PFN_LCLETTER;
            break;
        case rtfParNumLRoman:
            type = PFN_LCROMAN;
            break;

        case rtfParNumIndent:
            indent = info->rtfParam;
            break;
        case rtfParNumStartAt:
            start = info->rtfParam;
            break;
        }
    }

    if (type != -1)
    {
        info->fmt.dwMask |= (PFM_NUMBERING | PFM_NUMBERINGSTART | PFM_NUMBERINGSTYLE | PFM_NUMBERINGTAB);
        info->fmt.wNumbering = type;
        info->fmt.wNumberingStart = start;
        info->fmt.wNumberingStyle = PFNS_PAREN;
        if (type != PFN_BULLET)
        {
            if (txt_before == 0 && txt_after == 0)
                info->fmt.wNumberingStyle = PFNS_PLAIN;
            else if (txt_after == '.')
                info->fmt.wNumberingStyle = PFNS_PERIOD;
            else if (txt_before == '(' && txt_after == ')')
                info->fmt.wNumberingStyle = PFNS_PARENS;
        }
        info->fmt.wNumberingTab = indent;
    }

    TRACE("type %d indent %d start %d txt before %04x txt after %04x\n",
          type, indent, start, txt_before, txt_after);

    RTFRouteToken( info );     /* feed "}" back to router */
}