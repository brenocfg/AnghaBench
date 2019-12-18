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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  StringCchCopyNA (char*,size_t,int /*<<< orphan*/ ,size_t) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

LPSTR DuplicateStringAEx(LPCSTR str, size_t numOfChars)
{
    LPSTR dupStr;
    size_t strSize;

    if (!str) return NULL;

    strSize = min(strlen(str), numOfChars);

    dupStr = (LPSTR)MemAlloc(0, (strSize + 1) * sizeof(CHAR));
    if (!dupStr) return NULL;

    StringCchCopyNA(dupStr, strSize + 1, str, strSize);
    dupStr[strSize] = '\0';

    return dupStr;
}