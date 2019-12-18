#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {int* FileName; } ;
typedef  TYPE_1__* PDIRENTRY ;
typedef  char* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  RtlZeroMemory (char*,int) ; 

void FatParseShortFileName(PCHAR Buffer, PDIRENTRY DirEntry)
{
    ULONG        Idx;

    Idx = 0;
    RtlZeroMemory(Buffer, 13);

    //
    // Fixup first character
    //
    if (DirEntry->FileName[0] == 0x05)
    {
        DirEntry->FileName[0] = 0xE5;
    }

    //
    // Get the file name
    //
    while (Idx < 8)
    {
        if (DirEntry->FileName[Idx] == ' ')
        {
            break;
        }

        Buffer[Idx] = DirEntry->FileName[Idx];
        Idx++;
    }

    //
    // Get extension
    //
    if ((DirEntry->FileName[8] != ' '))
    {
        Buffer[Idx++] = '.';
        Buffer[Idx++] = (DirEntry->FileName[8] == ' ') ? '\0' : DirEntry->FileName[8];
        Buffer[Idx++] = (DirEntry->FileName[9] == ' ') ? '\0' : DirEntry->FileName[9];
        Buffer[Idx++] = (DirEntry->FileName[10] == ' ') ? '\0' : DirEntry->FileName[10];
    }

    //TRACE("FatParseShortFileName() ShortName = %s\n", Buffer);
}