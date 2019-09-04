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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__* PULONG ;
typedef  char* PCHAR ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 

__attribute__((used)) static
PCHAR
IniCacheGetKeyName(
    PCHAR Ptr,
    PCHAR *NamePtr,
    PULONG NameSize)
{
    ULONG Size = 0;

    *NamePtr = NULL;
    *NameSize = 0;

    while (Ptr && *Ptr)
    {
        *NamePtr = NULL;
        *NameSize = 0;
        Size = 0;

        /* Skip whitespace and empty lines */
        while (isspace(*Ptr) || *Ptr == '\n' || *Ptr == '\r')
        {
            Ptr++;
        }
        if (*Ptr == 0)
        {
            continue;
        }

        *NamePtr = Ptr;

        while (*Ptr != 0 && !isspace(*Ptr) && *Ptr != '=' && *Ptr != ';')
        {
            Size++;
            Ptr++;
        }
        if (*Ptr == ';')
        {
            while (*Ptr != 0 && *Ptr != '\r' && *Ptr != '\n')
            {
                Ptr++;
            }
        }
        else
        {
            *NameSize = Size;
            break;
        }
    }

  return Ptr;
}