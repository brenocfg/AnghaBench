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
typedef  int /*<<< orphan*/  VOID ;
typedef  char* PCSTR ;
typedef  char* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,char*) ; 
 size_t strlen (char*) ; 

VOID FsGetFirstNameFromPath(PCHAR Buffer, PCSTR Path)
{
    size_t i;
    size_t len;

    len = strlen(Path);

    // Copy all the characters up to the end of the
    // string or until we hit a '\' character
    // and put them in Buffer
    for (i = 0; i < len; i++)
    {
        if ((Path[i] == '\\') || (Path[i] == '/'))
        {
            break;
        }
        else
        {
            Buffer[i] = Path[i];
        }
    }

    Buffer[i] = 0;

    TRACE("FsGetFirstNameFromPath() Path = %s FirstName = %s\n", Path, Buffer);
}