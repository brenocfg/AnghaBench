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
struct TYPE_4__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static BOOL HLPFILE_GetContext(HLPFILE *hlpfile)
{
    BYTE                *cbuf, *cend;
    unsigned            clen;

    if (!HLPFILE_FindSubFile(hlpfile, "|CONTEXT",  &cbuf, &cend))
    {WINE_WARN("context0\n"); return FALSE;}

    clen = cend - cbuf;
    hlpfile->Context = HeapAlloc(GetProcessHeap(), 0, clen);
    if (!hlpfile->Context) return FALSE;
    memcpy(hlpfile->Context, cbuf, clen);

    return TRUE;
}