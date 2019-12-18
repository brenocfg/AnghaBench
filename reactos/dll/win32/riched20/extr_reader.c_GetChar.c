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
struct TYPE_4__ {int* rtfTextBuf; size_t rtfTextLen; int prevChar; int rtfLinePos; int /*<<< orphan*/  rtfLineNum; void* bumpLine; } ;
typedef  TYPE_1__ RTF_Info ;
typedef  void* BOOL ;

/* Variables and functions */
 int EOF ; 
 void* FALSE ; 
 void* TRUE ; 
 int _RTFGetChar (TYPE_1__*) ; 

__attribute__((used)) static int GetChar(RTF_Info *info)
{
	int	c;
        BOOL    oldBumpLine;

	if ((c = _RTFGetChar(info)) != EOF)
	{
		info->rtfTextBuf[info->rtfTextLen++] = c;
		info->rtfTextBuf[info->rtfTextLen] = '\0';
	}
	if (info->prevChar == EOF)
                info->bumpLine = TRUE;
        oldBumpLine = info->bumpLine; /* TRUE if prev char was line ending */
        info->bumpLine = FALSE;
	if (c == '\r')
                info->bumpLine = TRUE;
	else if (c == '\n')
	{
                info->bumpLine = TRUE;
		if (info->prevChar == '\r')		/* oops, previous \r wasn't */
                        oldBumpLine = FALSE;	/* really a line ending */
	}
	++info->rtfLinePos;
	if (oldBumpLine)	/* were we supposed to increment the */
	{			/* line count on this char? */
		++info->rtfLineNum;
		info->rtfLinePos = 1;
	}
	info->prevChar = c;
	return (c);
}