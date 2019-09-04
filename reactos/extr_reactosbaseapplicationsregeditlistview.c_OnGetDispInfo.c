#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  dwValType; } ;
struct TYPE_5__ {char* pszText; int iSubItem; scalar_t__ lParam; scalar_t__ cchTextMax; } ;
struct TYPE_6__ {TYPE_1__ item; } ;
typedef  TYPE_2__ NMLVDISPINFO ;
typedef  TYPE_3__ LINE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (char*) ; 
 int /*<<< orphan*/  IDS_DEFAULT_VALUE_NAME ; 
 int /*<<< orphan*/  IDS_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
#define  REG_BINARY 139 
#define  REG_DWORD 138 
#define  REG_DWORD_BIG_ENDIAN 137 
#define  REG_EXPAND_SZ 136 
#define  REG_FULL_RESOURCE_DESCRIPTOR 135 
#define  REG_LINK 134 
#define  REG_MULTI_SZ 133 
#define  REG_NONE 132 
#define  REG_QWORD 131 
#define  REG_RESOURCE_LIST 130 
#define  REG_RESOURCE_REQUIREMENTS_LIST 129 
#define  REG_SZ 128 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  wsprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OnGetDispInfo(NMLVDISPINFO* plvdi)
{
    static WCHAR buffer[200];

    plvdi->item.pszText = NULL;
    plvdi->item.cchTextMax = 0;

    switch (plvdi->item.iSubItem)
    {
    case 0:
        LoadStringW(hInst, IDS_DEFAULT_VALUE_NAME, buffer, COUNT_OF(buffer));
        plvdi->item.pszText = buffer;
        break;
    case 1:
        switch (((LINE_INFO*)plvdi->item.lParam)->dwValType)
        {
            case REG_NONE:
                plvdi->item.pszText = L"REG_NONE";
                break;
            case REG_SZ:
                plvdi->item.pszText = L"REG_SZ";
                break;
            case REG_EXPAND_SZ:
                plvdi->item.pszText = L"REG_EXPAND_SZ";
                break;
            case REG_BINARY:
                plvdi->item.pszText = L"REG_BINARY";
                break;
            case REG_DWORD: /* REG_DWORD_LITTLE_ENDIAN */
                plvdi->item.pszText = L"REG_DWORD";
                break;
            case REG_DWORD_BIG_ENDIAN:
                plvdi->item.pszText = L"REG_DWORD_BIG_ENDIAN";
                break;
            case REG_LINK:
                plvdi->item.pszText = L"REG_LINK";
                break;
            case REG_MULTI_SZ:
                plvdi->item.pszText = L"REG_MULTI_SZ";
                break;
            case REG_RESOURCE_LIST:
                plvdi->item.pszText = L"REG_RESOURCE_LIST";
                break;
            case REG_FULL_RESOURCE_DESCRIPTOR:
                plvdi->item.pszText = L"REG_FULL_RESOURCE_DESCRIPTOR";
                break;
            case REG_RESOURCE_REQUIREMENTS_LIST:
                plvdi->item.pszText = L"REG_RESOURCE_REQUIREMENTS_LIST";
                break;
            case REG_QWORD: /* REG_QWORD_LITTLE_ENDIAN */
                plvdi->item.pszText = L"REG_QWORD";
                break;
            default:
            {
                WCHAR buf2[200];
                LoadStringW(hInst, IDS_UNKNOWN_TYPE, buf2, COUNT_OF(buf2));
                wsprintf(buffer, buf2, ((LINE_INFO*)plvdi->item.lParam)->dwValType);
                plvdi->item.pszText = buffer;
                break;
            }
        }
        break;
    case 3:
        plvdi->item.pszText = L"";
        break;
    }
}