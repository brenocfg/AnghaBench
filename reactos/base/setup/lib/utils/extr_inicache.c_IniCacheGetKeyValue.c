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
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 

__attribute__((used)) static
PCHAR
IniCacheGetKeyValue(
    PCHAR Ptr,
    PCHAR *DataPtr,
    PULONG DataSize,
    BOOLEAN String)
{
    ULONG Size = 0;

    *DataPtr = NULL;
    *DataSize = 0;

    /* Skip whitespace */
    while (*Ptr != 0 && isspace(*Ptr))
    {
        Ptr++;
    }

    /* Check and skip '=' */
    if (*Ptr != '=')
    {
        return NULL;
    }
    Ptr++;

    /* Skip whitespace */
    while (*Ptr != 0 && isspace(*Ptr))
    {
        Ptr++;
    }

    if (*Ptr == '"' && String)
    {
        Ptr++;

        /* Get data */
        *DataPtr = Ptr;
        while (*Ptr != '"')
        {
            Ptr++;
            Size++;
        }
        Ptr++;

        while (*Ptr && *Ptr != '\r' && *Ptr != '\n')
        {
            Ptr++;
        }
    }
    else
    {
        /* Get data */
        *DataPtr = Ptr;
        while (*Ptr != 0 && *Ptr != '\r' && *Ptr != ';')
        {
            Ptr++;
            Size++;
        }
    }

    /* Skip to next line */
    if (*Ptr == '\r')
        Ptr++;
    if (*Ptr == '\n')
        Ptr++;

    *DataSize = Size;

    return Ptr;
}