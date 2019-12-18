#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int INT ;
typedef  int /*<<< orphan*/  ENCODING ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ENCODING_ANSI ; 
 int /*<<< orphan*/  ENCODING_UTF16BE ; 
 int /*<<< orphan*/  ENCODING_UTF16LE ; 
 int /*<<< orphan*/  ENCODING_UTF8 ; 
 int IS_TEXT_UNICODE_ILLEGAL_CHARS ; 
 int IS_TEXT_UNICODE_REVERSE_MASK ; 
 int IS_TEXT_UNICODE_STATISTICS ; 
 scalar_t__ IsTextNonZeroASCII (char const*,int) ; 
 scalar_t__ IsTextUnicode (char const*,int,int*) ; 
 int /*<<< orphan*/  MB_ERR_INVALID_CHARS ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ENCODING AnalyzeEncoding(const char *pBytes, DWORD dwSize)
{
    INT flags = IS_TEXT_UNICODE_STATISTICS;

    if (dwSize <= 1)
        return ENCODING_ANSI;

    if (IsTextNonZeroASCII(pBytes, dwSize))
    {
        return ENCODING_ANSI;
    }

    if (IsTextUnicode(pBytes, dwSize, &flags))
    {
        return ENCODING_UTF16LE;
    }

    if ((flags & IS_TEXT_UNICODE_REVERSE_MASK) && !(flags & IS_TEXT_UNICODE_ILLEGAL_CHARS))
    {
        return ENCODING_UTF16BE;
    }

    /* is it UTF-8? */
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pBytes, dwSize, NULL, 0))
    {
        return ENCODING_UTF8;
    }

    return ENCODING_ANSI;
}