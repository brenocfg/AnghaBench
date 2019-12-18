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
typedef  size_t ULONG ;
typedef  size_t* PULONG ;
typedef  char* PCHAR ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,size_t) ; 

__attribute__((used)) static
PCHAR
IniCacheGetSectionName(
    PCHAR Ptr,
    PCHAR *NamePtr,
    PULONG NameSize)
{
    ULONG Size = 0;
    CHAR Name[256];

    *NamePtr = NULL;
    *NameSize = 0;

    /* Skip whitespace */
    while (*Ptr != 0 && isspace(*Ptr))
    {
        Ptr++;
    }

    *NamePtr = Ptr;

    while (*Ptr != 0 && *Ptr != ']')
    {
        Size++;
        Ptr++;
    }
    Ptr++;

    while (*Ptr != 0 && *Ptr != L'\n')
    {
        Ptr++;
    }
    Ptr++;

    *NameSize = Size;

    strncpy(Name, *NamePtr, Size);
    Name[Size] = 0;

    DPRINT("SectionName: '%s'\n", Name);

    return Ptr;
}