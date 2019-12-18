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
typedef  int WCHAR ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */

__attribute__((used)) static void ReplaceInsertChars(HDC hdc, INT cWalk, INT* pcChars, WCHAR *pwOutChars, const WCHAR *replacements)
{
    int i;

    /* Replace */
    pwOutChars[cWalk] = replacements[0];
    cWalk=cWalk+1;

    /* Insert */
    for (i = 1; i < 3 && replacements[i] != 0x0000; i++)
    {
        int j;
        for (j = *pcChars; j > cWalk; j--)
            pwOutChars[j] = pwOutChars[j-1];
        *pcChars= *pcChars+1;
        pwOutChars[cWalk] = replacements[i];
        cWalk = cWalk+1;
    }
}