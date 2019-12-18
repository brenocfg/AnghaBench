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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  StringCchCopyA (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

LPSTR DuplicateStringA(LPCSTR str)
{
    LPSTR dupStr;
    size_t strSizePlusNull;

    if (!str) return NULL;

    strSizePlusNull = strlen(str) + 1;

    dupStr = (LPSTR)MemAlloc(0, strSizePlusNull * sizeof(CHAR));
    if (!dupStr) return NULL;

    StringCchCopyA(dupStr, strSizePlusNull, str);

    return dupStr;
}