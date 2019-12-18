#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rtfFormat; scalar_t__ rtfMajor; char* rtfTextBuf; size_t rtfTextLen; int rtfClass; int pushedClass; scalar_t__ pushedMajor; int /*<<< orphan*/  pushedTextBuf; int /*<<< orphan*/  pushedParam; int /*<<< orphan*/  rtfParam; scalar_t__ pushedMinor; scalar_t__ rtfMinor; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ GetChar (TYPE_1__*) ; 
 scalar_t__ SF_TEXT ; 
 int /*<<< orphan*/  _RTFGetToken2 (TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,int /*<<< orphan*/ ) ; 
 size_t lstrlenA (char*) ; 
 int rtfEOF ; 
 int /*<<< orphan*/  rtfNoParam ; 
 int rtfText ; 

__attribute__((used)) static void _RTFGetToken(RTF_Info *info)
{
	if (info->rtfFormat == SF_TEXT)
	{
		info->rtfMajor = GetChar (info);
		info->rtfMinor = 0;
		info->rtfParam = rtfNoParam;
		info->rtfTextBuf[info->rtfTextLen = 0] = '\0';
		if (info->rtfMajor == EOF)
			info->rtfClass = rtfEOF;
		else
			info->rtfClass = rtfText;
		return;
	}

	/* first check for pushed token from RTFUngetToken() */

	if (info->pushedClass >= 0)
	{
		info->rtfClass = info->pushedClass;
		info->rtfMajor = info->pushedMajor;
		info->rtfMinor = info->pushedMinor;
		info->rtfParam = info->pushedParam;
		lstrcpyA (info->rtfTextBuf, info->pushedTextBuf);
		info->rtfTextLen = lstrlenA(info->rtfTextBuf);
		info->pushedClass = -1;
		return;
	}

	/*
	 * Beyond this point, no token is ever seen twice, which is
	 * important, e.g., for making sure no "}" pops the font stack twice.
	 */

	_RTFGetToken2 (info);
}