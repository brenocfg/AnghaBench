#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_22__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  SectionItemList; int /*<<< orphan*/  SectionItemCount; void* ItemValue; struct TYPE_22__* ItemName; void* SectionName; } ;
typedef  TYPE_1__* PINI_SECTION_ITEM ;
typedef  TYPE_1__* PINI_SECTION ;
typedef  TYPE_1__* PCHAR ;
typedef  int /*<<< orphan*/  INI_SECTION_ITEM ;
typedef  int /*<<< orphan*/  INI_SECTION ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 void* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IniExtractSectionName (void*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IniExtractSettingName (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IniExtractSettingValue (void*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IniFileSectionCount ; 
 scalar_t__ IniFileSectionInitialized ; 
 int /*<<< orphan*/  IniFileSectionListHead ; 
 int /*<<< orphan*/  IniFileSettingCount ; 
 scalar_t__ IniGetNextLine (TYPE_1__*,scalar_t__,TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ IniGetNextLineSize (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int IniGetSectionNameSize (TYPE_1__*,scalar_t__) ; 
 int IniGetSettingNameSize (TYPE_1__*,scalar_t__) ; 
 int IniGetSettingValueSize (TYPE_1__*,scalar_t__) ; 
 scalar_t__ IniIsCommentLine (TYPE_1__*,scalar_t__) ; 
 scalar_t__ IniIsLineEmpty (TYPE_1__*,scalar_t__) ; 
 scalar_t__ IniIsSectionName (TYPE_1__*,scalar_t__) ; 
 scalar_t__ IniIsSetting (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MachConsGetCh () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TAG_INI_FILE ; 
 int /*<<< orphan*/  TAG_INI_NAME ; 
 int /*<<< orphan*/  TAG_INI_SECTION ; 
 int /*<<< orphan*/  TAG_INI_SECTION_ITEM ; 
 int /*<<< orphan*/  TAG_INI_VALUE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (TYPE_1__*) ; 

BOOLEAN IniParseFile(PCHAR IniFileData, ULONG IniFileSize)
{
    ULONG                    CurrentOffset;
    ULONG                    CurrentLineNumber;
    PCHAR                IniFileLine;
    ULONG                    IniFileLineSize;
    ULONG                    LineLength;
    PINI_SECTION        CurrentSection = NULL;
    PINI_SECTION_ITEM    CurrentItem = NULL;

    TRACE("IniParseFile() IniFileSize: %d\n", IniFileSize);

    if (!IniFileSectionInitialized)
    {
        InitializeListHead(&IniFileSectionListHead);
        IniFileSectionInitialized = TRUE;
    }

    // Start with an 80-byte buffer
    IniFileLineSize = 80;
    IniFileLine = FrLdrTempAlloc(IniFileLineSize, TAG_INI_FILE);
    if (!IniFileLine)
    {
        return FALSE;
    }

    // Loop through each line and parse it
    CurrentLineNumber = 0;
    CurrentOffset = 0;
    while (CurrentOffset < IniFileSize)
    {
        // First check the line size and increase our buffer if necessary
        if (IniFileLineSize < IniGetNextLineSize(IniFileData, IniFileSize, CurrentOffset))
        {
            IniFileLineSize = IniGetNextLineSize(IniFileData, IniFileSize, CurrentOffset);
            FrLdrTempFree(IniFileLine, TAG_INI_FILE);
            IniFileLine = FrLdrTempAlloc(IniFileLineSize, TAG_INI_FILE);
            if (!IniFileLine)
            {
                return FALSE;
            }
        }

        // Get the line of data
        CurrentOffset = IniGetNextLine(IniFileData, IniFileSize, IniFileLine, IniFileLineSize, CurrentOffset);
        LineLength = (ULONG)strlen(IniFileLine);

        // If it is a blank line or a comment then skip it
        if (IniIsLineEmpty(IniFileLine, LineLength) || IniIsCommentLine(IniFileLine, LineLength))
        {
            CurrentLineNumber++;
            continue;
        }

        // Check if it is a new section
        if (IniIsSectionName(IniFileLine, LineLength))
        {
            // Allocate a new section structure
            CurrentSection = FrLdrTempAlloc(sizeof(INI_SECTION), TAG_INI_SECTION);
            if (!CurrentSection)
            {
                FrLdrTempFree(IniFileLine, TAG_INI_FILE);
                return FALSE;
            }

            RtlZeroMemory(CurrentSection, sizeof(INI_SECTION));

            // Allocate the section name buffer
            CurrentSection->SectionName = FrLdrTempAlloc(IniGetSectionNameSize(IniFileLine, LineLength), TAG_INI_NAME);
            if (!CurrentSection->SectionName)
            {
                FrLdrTempFree(CurrentSection, TAG_INI_FILE);
                FrLdrTempFree(IniFileLine, TAG_INI_FILE);
                return FALSE;
            }

            // Get the section name
            IniExtractSectionName(CurrentSection->SectionName, IniFileLine, LineLength);
            InitializeListHead(&CurrentSection->SectionItemList);

            // Add it to the section list head
            IniFileSectionCount++;
            InsertTailList(&IniFileSectionListHead, &CurrentSection->ListEntry);

            CurrentLineNumber++;
            continue;
        }

        // Check if it is a setting
        if (IniIsSetting(IniFileLine, LineLength))
        {
            // First check to make sure we're inside a [section]
            if (CurrentSection == NULL)
            {
                printf("Error: freeldr.ini:%lu: Setting '%s' found outside of a [section].\n", CurrentLineNumber, IniFileLine);
                printf("Press any key to continue...\n");
                MachConsGetCh();
                CurrentLineNumber++;
                continue;
            }

            // Allocate a new item structure
            CurrentItem = FrLdrTempAlloc(sizeof(INI_SECTION_ITEM), TAG_INI_SECTION_ITEM);
            if (!CurrentItem)
            {
                FrLdrTempFree(IniFileLine, TAG_INI_FILE);
                return FALSE;
            }

            RtlZeroMemory(CurrentItem, sizeof(INI_SECTION_ITEM));

            // Allocate the setting name buffer
            CurrentItem->ItemName = FrLdrTempAlloc(IniGetSettingNameSize(IniFileLine, LineLength), TAG_INI_NAME);
            if (!CurrentItem->ItemName)
            {
                FrLdrTempFree(CurrentItem, TAG_INI_SECTION_ITEM);
                FrLdrTempFree(IniFileLine, TAG_INI_FILE);
                return FALSE;
            }

            // Allocate the setting value buffer
            CurrentItem->ItemValue = FrLdrTempAlloc(IniGetSettingValueSize(IniFileLine, LineLength), TAG_INI_VALUE);
            if (!CurrentItem->ItemValue)
            {
                FrLdrTempFree(CurrentItem->ItemName, TAG_INI_NAME);
                FrLdrTempFree(CurrentItem, TAG_INI_SECTION_ITEM);
                FrLdrTempFree(IniFileLine, TAG_INI_FILE);
                return FALSE;
            }

            // Get the section name
            IniExtractSettingName(CurrentItem->ItemName, IniFileLine, LineLength);
            IniExtractSettingValue(CurrentItem->ItemValue, IniFileLine, LineLength);

            // Add it to the current section
            IniFileSettingCount++;
            CurrentSection->SectionItemCount++;
            InsertTailList(&CurrentSection->SectionItemList, &CurrentItem->ListEntry);

            CurrentLineNumber++;
            continue;
        }

        CurrentLineNumber++;
    }

    FrLdrTempFree(IniFileLine, TAG_INI_FILE);

    TRACE("Parsed %d sections and %d settings.\n", IniFileSectionCount, IniFileSettingCount);
    TRACE("IniParseFile() done.\n");

    return TRUE;
}