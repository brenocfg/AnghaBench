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
typedef  int /*<<< orphan*/  szIntType ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_ETH ; 
 int /*<<< orphan*/  IDS_FDDI ; 
 int /*<<< orphan*/  IDS_LOOP ; 
 int /*<<< orphan*/  IDS_OTHER ; 
 int /*<<< orphan*/  IDS_PPP ; 
 int /*<<< orphan*/  IDS_SLIP ; 
 int /*<<< orphan*/  IDS_TOKEN ; 
 int /*<<< orphan*/  IDS_UNKNOWN ; 
 int /*<<< orphan*/  LoadStringAndOem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
#define  MIB_IF_TYPE_ETHERNET 134 
#define  MIB_IF_TYPE_FDDI 133 
#define  MIB_IF_TYPE_LOOPBACK 132 
#define  MIB_IF_TYPE_OTHER 131 
#define  MIB_IF_TYPE_PPP 130 
#define  MIB_IF_TYPE_SLIP 129 
#define  MIB_IF_TYPE_TOKENRING 128 
 int /*<<< orphan*/  hInstance ; 

LPTSTR GetInterfaceTypeName(UINT InterfaceType)
{
    static TCHAR szIntType[25];

    switch (InterfaceType)
    {
        case MIB_IF_TYPE_OTHER:
            if (!LoadStringAndOem(hInstance, IDS_OTHER, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_ETHERNET:
            if (!LoadStringAndOem(hInstance, IDS_ETH, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_TOKENRING:
            if (!LoadStringAndOem(hInstance, IDS_TOKEN, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_FDDI:
            if (!LoadStringAndOem(hInstance, IDS_FDDI, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_PPP:
            if (!LoadStringAndOem(hInstance, IDS_PPP, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_LOOPBACK:
            if (!LoadStringAndOem(hInstance, IDS_LOOP, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        case MIB_IF_TYPE_SLIP:
            if (!LoadStringAndOem(hInstance, IDS_SLIP, szIntType, sizeof(szIntType)))
                return NULL;
            break;

        default:
            if (!LoadStringAndOem(hInstance, IDS_UNKNOWN, szIntType, sizeof(szIntType)))
                return NULL;
            break;
    }

    return szIntType;
}