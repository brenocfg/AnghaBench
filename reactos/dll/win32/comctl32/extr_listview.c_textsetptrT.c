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
typedef  scalar_t__ LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Free (scalar_t__) ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  Str_SetPtrW (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_text (scalar_t__) ; 
 scalar_t__ textdupTtoW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textfreeT (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL textsetptrT(LPWSTR *dest, LPCWSTR src, BOOL isW)
{
    BOOL bResult = TRUE;
    
    if (src == LPSTR_TEXTCALLBACKW)
    {
	if (is_text(*dest)) Free(*dest);
	*dest = LPSTR_TEXTCALLBACKW;
    }
    else
    {
	LPWSTR pszText = textdupTtoW(src, isW);
	if (*dest == LPSTR_TEXTCALLBACKW) *dest = NULL;
	bResult = Str_SetPtrW(dest, pszText);
	textfreeT(pszText, isW);
    }
    return bResult;
}