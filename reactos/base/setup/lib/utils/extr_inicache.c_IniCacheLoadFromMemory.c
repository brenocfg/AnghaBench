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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * PINICACHESECTION ;
typedef  int /*<<< orphan*/ * PINICACHEKEY ;
typedef  int /*<<< orphan*/ * PINICACHE ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  INICACHE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * IniCacheAddKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IniCacheAddSection (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* IniCacheGetKeyName (char*,char**,int /*<<< orphan*/ *) ; 
 char* IniCacheGetKeyValue (char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* IniCacheGetSectionName (char*,char**,int /*<<< orphan*/ *) ; 
 char* IniCacheSkipToNextSection (char*) ; 
 char* IniCacheSkipWhitespace (char*) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
IniCacheLoadFromMemory(
    PINICACHE *Cache,
    PCHAR FileBuffer,
    ULONG FileLength,
    BOOLEAN String)
{
    PCHAR Ptr;

    PINICACHESECTION Section;
    PINICACHEKEY Key;

    PCHAR SectionName;
    ULONG SectionNameSize;

    PCHAR KeyName;
    ULONG KeyNameSize;

    PCHAR KeyValue;
    ULONG KeyValueSize;

    /* Allocate inicache header */
    *Cache = (PINICACHE)RtlAllocateHeap(ProcessHeap,
                                        HEAP_ZERO_MEMORY,
                                        sizeof(INICACHE));
    if (*Cache == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Parse ini file */
    Section = NULL;
    Ptr = FileBuffer;
    while (Ptr != NULL && *Ptr != 0)
    {
        Ptr = IniCacheSkipWhitespace(Ptr);
        if (Ptr == NULL)
            continue;

        if (*Ptr == '[')
        {
            Section = NULL;
            Ptr++;

            Ptr = IniCacheGetSectionName(Ptr,
                                         &SectionName,
                                         &SectionNameSize);

            DPRINT("[%.*s]\n", SectionNameSize, SectionName);

            Section = IniCacheAddSection(*Cache,
                                         SectionName,
                                         SectionNameSize);
            if (Section == NULL)
            {
                DPRINT("IniCacheAddSection() failed\n");
                Ptr = IniCacheSkipToNextSection(Ptr);
                continue;
            }
        }
        else
        {
            if (Section == NULL)
            {
                Ptr = IniCacheSkipToNextSection(Ptr);
                continue;
            }

            Ptr = IniCacheGetKeyName(Ptr,
                                     &KeyName,
                                     &KeyNameSize);

            Ptr = IniCacheGetKeyValue(Ptr,
                                      &KeyValue,
                                      &KeyValueSize,
                                      String);

            DPRINT("'%.*s' = '%.*s'\n", KeyNameSize, KeyName, KeyValueSize, KeyValue);

            Key = IniCacheAddKey(Section,
                                 KeyName,
                                 KeyNameSize,
                                 KeyValue,
                                 KeyValueSize);
            if (Key == NULL)
            {
                DPRINT("IniCacheAddKey() failed\n");
            }
        }
    }

    return STATUS_SUCCESS;
}