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
struct TYPE_2__ {int memsize; char* mem; scalar_t__ mempos; int /*<<< orphan*/  memfree; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int GetFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* bc ; 
 scalar_t__ cmd_alloc (int) ; 

void BatchFile2Mem(HANDLE hBatchFile)
{
    TRACE ("BatchFile2Mem ()\n");

    bc->memsize = GetFileSize(hBatchFile, NULL);
    bc->mem     = (char *)cmd_alloc(bc->memsize+1);		/* 1 extra for '\0' */

    /* if memory is available, read it in and close the file */
    if (bc->mem != NULL)
    {
        TRACE ("BatchFile2Mem memory %08x - %08x\n",bc->mem,bc->memsize);
        SetFilePointer (hBatchFile, 0, NULL, FILE_BEGIN);
        ReadFile(hBatchFile, (LPVOID)bc->mem, bc->memsize,  &bc->memsize, NULL);
        bc->mem[bc->memsize]='\0';  /* end this, so you can dump it as a string */
        bc->memfree=TRUE;           /* this one needs to be freed */
    }
    else
    {
        bc->memsize=0;              /* this will prevent mem being accessed */
        bc->memfree=FALSE;
    }
    bc->mempos = 0;                 /* set position to the start */
}