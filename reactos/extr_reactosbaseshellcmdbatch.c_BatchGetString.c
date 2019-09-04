#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* mem; scalar_t__ mempos; scalar_t__ memsize; } ;
typedef  char* LPTSTR ;
typedef  char* LPSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* bc ; 

BOOL BatchGetString(LPTSTR lpBuffer, INT nBufferLength)
{
    LPSTR lpString;
    INT len = 0;
#ifdef _UNICODE
    lpString = cmd_alloc(nBufferLength);
    if (!lpString)
    {
        WARN("Cannot allocate memory for lpString\n");
        error_out_of_memory();
        return FALSE;
    }
#else
    lpString = lpBuffer;
#endif
    /* read all chars from memory until a '\n' is encountered */
    if (bc->mem)
    {
        for (; (bc->mempos < bc->memsize  &&  len < (nBufferLength-1)); len++)
        { 
            lpString[len] = bc->mem[bc->mempos++];
            if (lpString[len] == '\n' )
            {
                len++;
                break;
            }
        }
    }

    if (!len)
    {
#ifdef _UNICODE
        cmd_free(lpString);
#endif
        return FALSE;
    }

    lpString[len++] = '\0';
#ifdef _UNICODE
    MultiByteToWideChar(OutputCodePage, 0, lpString, -1, lpBuffer, len);
    cmd_free(lpString);
#endif
    return TRUE;
}