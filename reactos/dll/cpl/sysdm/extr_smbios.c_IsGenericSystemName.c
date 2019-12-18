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
typedef  size_t UINT ;
struct TYPE_3__ {char* member_0; int member_1; int member_2; int bRemove; int /*<<< orphan*/  pwName; scalar_t__ bCaseSensitive; } ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  TYPE_1__ GENERIC_NAME ;
typedef  int BOOL ;

/* Variables and functions */
#define  FALSE 129 
#define  TRUE 128 
 size_t _countof (TYPE_1__ const*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL IsGenericSystemName(PCWSTR ven, PCWSTR dev, BOOL * bRemove)
{
    static const GENERIC_NAME Vendors[] =
    {
        // some ASUS boards
        { L"To Be Filled By O.E.M.", FALSE, TRUE },
        { L"To Be Filled By O.E.M", FALSE, TRUE },
        { L"System manufacturer", FALSE, TRUE },
        // some Gigabyte boards
        { L"Default string", TRUE, TRUE },
        { L"LTD Delovoy Office", TRUE, FALSE },
        { L"Motherboard by ZOTAC", TRUE, FALSE },
        // various boards
        { L"Type2 - Board Vendor Name1", TRUE, TRUE },
        { L"DEPO Computers", TRUE, FALSE },
        { L"-", TRUE, TRUE },
        { L"OEM", TRUE, TRUE },
        { L"O.E.M", TRUE, TRUE },
        { L"Unknow", TRUE, TRUE },
        // distinguish between Oracle and older VirtualBox releases (Sun, etc.)
        { L"innotek GmbH", TRUE, FALSE },
    };
    static const GENERIC_NAME Devices[] =
    {
        // some ASUS boards
        { L"To Be Filled By O.E.M.", FALSE, TRUE },
        { L"To Be Filled By O.E.M", FALSE, TRUE },
        { L"All Series", TRUE, TRUE },
        { L"System Product Name", TRUE, TRUE },
        { L"System Name", TRUE, TRUE },
        // some Gigabyte boards
        { L"Default string", TRUE, TRUE },
        // some MSI boards
        { L"Please change product name", TRUE, TRUE },
        // some Intel boards
        { L"Computer", TRUE, TRUE },
        { L"ChiefRiver Platform", TRUE, FALSE },
        { L"OakTrail Platform", TRUE, FALSE },
        { L"SharkBay Platform", TRUE, FALSE },
        { L"HuronRiver Platform", TRUE, FALSE },
        { L"SandyBridge Platform", TRUE, FALSE },
        { L"Broadwell Platform", TRUE, FALSE },
        { L"Sabine Platform", TRUE, FALSE },
        // various boards
        { L"Base Board Product Name", TRUE, TRUE },
        { L"Base Board Version", TRUE, TRUE },
        { L"Type2 - Board Product Name1", TRUE, TRUE },
        { L"Type2 - Board Version", TRUE, TRUE },
        { L"*", TRUE, TRUE },
        { L"T", TRUE, TRUE },
        { L"GEG", TRUE, TRUE },
        { L"N/A", TRUE, TRUE },
        { L"---", TRUE, TRUE },
        { L"OEM", TRUE, TRUE },
        { L"INVA", TRUE, TRUE },
        { L"O.E.M", TRUE, TRUE },
        { L"DNSNB", TRUE, FALSE },
        { L"12345", TRUE, FALSE },
        { L"``````", TRUE, TRUE },
        { L"Uknown", TRUE, TRUE },
        { L"Desktop", FALSE, TRUE },
        { L"Invalid", FALSE, TRUE },
        { L"Reserved", TRUE, TRUE },
        { L"HaierComputer", TRUE, FALSE },
        { L"DEPO Computers", TRUE, FALSE },
        { L"InsydeH2O EFI BIOS", TRUE, TRUE },
        { L"HP All-in-One", TRUE, FALSE },
        { L"MP Server", TRUE, FALSE },
        { L"0000000000", TRUE, TRUE },
        // some Foxconn boards
        { L"Aquarius Pro, Std, Elt Series", TRUE, FALSE },
        // some ASUS server boards
        { L"Aquarius Server", TRUE, FALSE },
        { L"Aquarius Server G2", TRUE, FALSE },
        // some Supermicro server boards
        { L"Super Server", TRUE, FALSE },
        // some Positivo devices
        { L"POSITIVO MOBILE", FALSE, FALSE },
    };
    BOOL bMatch;
    UINT i;

    if (bRemove)
    {
        *bRemove = FALSE;
    }
    for (i = 0; i < _countof(Vendors); i++)
    {
        if (!ven)
        {
            break;
        }
        if (Vendors[i].bCaseSensitive)
        {
            bMatch = !wcscmp(ven, Vendors[i].pwName);
        }
        else
        {
            bMatch = !wcsicmp(ven, Vendors[i].pwName);
        }
        if (bMatch)
        {
            if (bRemove)
            {
                *bRemove = Vendors[i].bRemove;
            }
            return TRUE;
        }
    }

    for (i = 0; i < _countof(Devices); i++)
    {
        if (!dev)
        {
            break;
        }
        if (Devices[i].bCaseSensitive)
        {
            bMatch = !wcscmp(dev, Devices[i].pwName);
        }
        else
        {
            bMatch = !wcsicmp(dev, Devices[i].pwName);
        }
        if (bMatch)
        {
            if (bRemove)
            {
                *bRemove = Devices[i].bRemove;
            }
            return TRUE;
        }
    }
    return FALSE;
}