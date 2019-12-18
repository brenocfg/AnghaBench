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
struct TYPE_9__ {int rtfParam; char* rtfTextBuf; size_t rtfTextLen; int pushedChar; int rtfMajor; void* rtfClass; TYPE_2__* stream; int /*<<< orphan*/  rtfMinor; } ;
struct TYPE_8__ {TYPE_1__* editstream; } ;
struct TYPE_7__ {int dwError; } ;
typedef  TYPE_3__ RTF_Info ;

/* Variables and functions */
 int EOF ; 
 int GetChar (TYPE_3__*) ; 
 int /*<<< orphan*/  Lookup (TYPE_3__*,char*) ; 
 int RTFCharToHex (int) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ isxdigit (int) ; 
 int rtfBeginGroup ; 
 void* rtfControl ; 
 void* rtfEOF ; 
 int rtfEndGroup ; 
 void* rtfGroup ; 
 int rtfNoParam ; 
 int rtfSpecialChar ; 
 int /*<<< orphan*/  rtfTab ; 
 void* rtfText ; 
 void* rtfUnknown ; 

__attribute__((used)) static void _RTFGetToken2(RTF_Info *info)
{
	int	sign;
	int	c;

	/* initialize token vars */

	info->rtfClass = rtfUnknown;
	info->rtfParam = rtfNoParam;
	info->rtfTextBuf[info->rtfTextLen = 0] = '\0';

	/* get first character, which may be a pushback from previous token */

	if (info->pushedChar != EOF)
	{
		c = info->pushedChar;
		info->rtfTextBuf[info->rtfTextLen++] = c;
		info->rtfTextBuf[info->rtfTextLen] = '\0';
		info->pushedChar = EOF;
	}
	else if ((c = GetChar (info)) == EOF)
	{
		info->rtfClass = rtfEOF;
		return;
	}

	if (c == '{')
	{
		info->rtfClass = rtfGroup;
		info->rtfMajor = rtfBeginGroup;
		return;
	}
	if (c == '}')
	{
		info->rtfClass = rtfGroup;
		info->rtfMajor = rtfEndGroup;
		return;
	}
	if (c != '\\')
	{
		/*
		 * Two possibilities here:
		 * 1) ASCII 9, effectively like \tab control symbol
		 * 2) literal text char
		 */
		if (c == '\t')			/* ASCII 9 */
		{
			info->rtfClass = rtfControl;
			info->rtfMajor = rtfSpecialChar;
			info->rtfMinor = rtfTab;
		}
		else
		{
			info->rtfClass = rtfText;
			info->rtfMajor = c;
		}
		return;
	}
	if ((c = GetChar (info)) == EOF)
	{
		/* early eof, whoops (class is rtfUnknown) */
		return;
	}
	if (!isalpha (c))
	{
		/*
		 * Three possibilities here:
		 * 1) hex encoded text char, e.g., \'d5, \'d3
		 * 2) special escaped text char, e.g., \{, \}
		 * 3) control symbol, e.g., \_, \-, \|, \<10>
		 */
		if (c == '\'')				/* hex char */
		{
		int	c2;

			if ((c = GetChar (info)) != EOF && (c2 = GetChar (info)) != EOF
				&& isxdigit(c) && isxdigit(c2))
			{
				info->rtfClass = rtfText;
				info->rtfMajor = RTFCharToHex (c) * 16 + RTFCharToHex (c2);
				return;
			}
			/* early eof, whoops */
			info->rtfClass = rtfEOF;
			info->stream->editstream->dwError = -14;
			return;
		}

		/* escaped char */
		/*if (index (":{}\\", c) != NULL)*/ /* escaped char */
		if (c == ':' || c == '{' || c == '}' || c == '\\')
		{
			info->rtfClass = rtfText;
			info->rtfMajor = c;
			return;
		}

		/* control symbol */
		Lookup (info, info->rtfTextBuf);	/* sets class, major, minor */
		return;
	}
	/* control word */
	while (isalpha (c))
	{
		if ((c = GetChar (info)) == EOF)
			break;
	}

	/*
	 * At this point, the control word is all collected, so the
	 * major/minor numbers are determined before the parameter
	 * (if any) is scanned.  There will be one too many characters
	 * in the buffer, though, so fix up before and restore after
	 * looking up.
	 */

	if (c != EOF)
		info->rtfTextBuf[info->rtfTextLen-1] = '\0';
	Lookup (info, info->rtfTextBuf);	/* sets class, major, minor */
	if (c != EOF)
		info->rtfTextBuf[info->rtfTextLen-1] = c;

	/*
	 * Should be looking at first digit of parameter if there
	 * is one, unless it's negative.  In that case, next char
	 * is '-', so need to gobble next char, and remember sign.
	 */

	sign = 1;
	if (c == '-')
	{
		sign = -1;
		c = GetChar (info);
	}
	if (c != EOF && isdigit (c))
	{
		info->rtfParam = 0;
		while (isdigit (c))	/* gobble parameter */
		{
			info->rtfParam = info->rtfParam * 10 + c - '0';
			if ((c = GetChar (info)) == EOF)
				break;
		}
		info->rtfParam *= sign;
	}
	/*
	 * If control symbol delimiter was a blank, gobble it.
	 * Otherwise the character is first char of next token, so
	 * push it back for next call.  In either case, delete the
	 * delimiter from the token buffer.
	 */
	if (c != EOF)
	{
		if (c != ' ')
			info->pushedChar = c;
		info->rtfTextBuf[--info->rtfTextLen] = '\0';
	}
}