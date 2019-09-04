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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  ItemValue; int /*<<< orphan*/  ItemName; } ;
typedef  TYPE_1__* PINI_SECTION_ITEM ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT_INIFILE ; 
 int /*<<< orphan*/  DbgDumpBuffer (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* IniGetSettingByNumber (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

BOOLEAN IniReadSettingByNumber(ULONG_PTR SectionId, ULONG SettingNumber, PCHAR SettingName, ULONG NameSize, PCHAR SettingValue, ULONG ValueSize)
{
    PINI_SECTION_ITEM    SectionItem;
    TRACE(".001 NameSize = %d ValueSize = %d\n", NameSize, ValueSize);

    TRACE("IniReadSettingByNumber() SectionId = 0x%x\n", SectionId);

    // Retrieve requested setting
    SectionItem = IniGetSettingByNumber(SectionId, SettingNumber);
    if (!SectionItem)
    {
        TRACE("IniReadSettingByNumber() Setting number %d not found.\n", SettingNumber);
        return FALSE;
    }

    TRACE("IniReadSettingByNumber() Setting number %d found.\n", SettingNumber);
    TRACE("IniReadSettingByNumber() Setting name = %s\n", SectionItem->ItemName);
    TRACE("IniReadSettingByNumber() Setting value = %s\n", SectionItem->ItemValue);

    TRACE("1 NameSize = %d ValueSize = %d\n", NameSize, ValueSize);
    TRACE("2 NameSize = %d ValueSize = %d\n", NameSize, ValueSize);
    strncpy(SettingName, SectionItem->ItemName, NameSize - 1);
    SettingName[NameSize - 1] = '\0';
    TRACE("3 NameSize = %d ValueSize = %d\n", NameSize, ValueSize);
    strncpy(SettingValue, SectionItem->ItemValue, ValueSize - 1);
    SettingValue[ValueSize - 1] = '\0';
    TRACE("4 NameSize = %d ValueSize = %d\n", NameSize, ValueSize);
    DbgDumpBuffer(DPRINT_INIFILE, SettingName, NameSize);
    DbgDumpBuffer(DPRINT_INIFILE, SettingValue, ValueSize);

    return TRUE;
}