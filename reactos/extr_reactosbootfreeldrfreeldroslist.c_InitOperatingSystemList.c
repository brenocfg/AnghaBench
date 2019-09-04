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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_4__ {void* OsLoadOptions; void* LoadIdentifier; void* SystemPartition; } ;
typedef  int /*<<< orphan*/  SettingValue ;
typedef  int /*<<< orphan*/  SettingName ;
typedef  char* PCSTR ;
typedef  char* PCHAR ;
typedef  TYPE_1__ OperatingSystemItem ;
typedef  char CHAR ;

/* Variables and functions */
 char ANSI_NULL ; 
 void* CopyString (char*) ; 
 TYPE_1__* FrLdrHeapAlloc (int,int /*<<< orphan*/ ) ; 
 int IniGetNumSectionItems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IniOpenSection (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IniReadSettingByNumber (int /*<<< orphan*/ ,int,char*,int,char*,int) ; 
 int /*<<< orphan*/  TAG_OS_ITEM ; 

OperatingSystemItem* InitOperatingSystemList(ULONG* OperatingSystemCountPointer)
{
    ULONG Idx;
    CHAR SettingName[260];
    CHAR SettingValue[260];
    ULONG_PTR SectionId;
    PCHAR TitleStart, TitleEnd;
    PCSTR OsLoadOptions;
    ULONG Count;
    OperatingSystemItem* Items;

    /* Open the [FreeLoader] section */
    if (!IniOpenSection("Operating Systems", &SectionId))
        return NULL;

    /* Count number of operating systems in the section */
    Count = IniGetNumSectionItems(SectionId);

    /* Allocate memory to hold operating system lists */
    Items = FrLdrHeapAlloc(Count * sizeof(OperatingSystemItem), TAG_OS_ITEM);
    if (!Items)
        return NULL;

    /* Now loop through and read the operating system section and display names */
    for (Idx = 0; Idx < Count; Idx++)
    {
        IniReadSettingByNumber(SectionId, Idx, SettingName, sizeof(SettingName), SettingValue, sizeof(SettingValue));

        /* Search start and end of the title */
        OsLoadOptions = NULL;
        TitleStart = SettingValue;
        while (*TitleStart == ' ' || *TitleStart == '"')
            TitleStart++;
        TitleEnd = TitleStart;
        if (*TitleEnd != ANSI_NULL)
            TitleEnd++;
        while (*TitleEnd != ANSI_NULL && *TitleEnd != '"')
            TitleEnd++;
        if (*TitleEnd != ANSI_NULL)
        {
            *TitleEnd = ANSI_NULL;
            OsLoadOptions = TitleEnd + 1;
        }

        /* Copy the system partition, identifier and options */
        Items[Idx].SystemPartition = CopyString(SettingName);
        Items[Idx].LoadIdentifier = CopyString(TitleStart);
        Items[Idx].OsLoadOptions = CopyString(OsLoadOptions);
    }

    /* Return success */
    *OperatingSystemCountPointer = Count;
    return Items;
}