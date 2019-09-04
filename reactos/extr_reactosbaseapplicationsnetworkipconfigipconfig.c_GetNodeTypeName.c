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
typedef  int /*<<< orphan*/  szNode ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_BCAST ; 
 int /*<<< orphan*/  IDS_HYBRID ; 
 int /*<<< orphan*/  IDS_MIXED ; 
 int /*<<< orphan*/  IDS_P2P ; 
 int /*<<< orphan*/  IDS_UNKNOWN ; 
 int /*<<< orphan*/  LoadStringAndOem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hInstance ; 

LPTSTR GetNodeTypeName(UINT NodeType)
{
    static TCHAR szNode[14];

    switch (NodeType)
    {
        case 1:
            if (!LoadStringAndOem(hInstance, IDS_BCAST, szNode,  sizeof(szNode)))
                return NULL;
            break;

        case 2:
            if (!LoadStringAndOem(hInstance, IDS_P2P, szNode,  sizeof(szNode)))
                return NULL;
            break;

        case 4:
            if (!LoadStringAndOem(hInstance, IDS_MIXED, szNode,  sizeof(szNode)))
                return NULL;
            break;

        case 8:
            if (!LoadStringAndOem(hInstance, IDS_HYBRID, szNode,  sizeof(szNode)))
                return NULL;
            break;

        default :
            if (!LoadStringAndOem(hInstance, IDS_UNKNOWN, szNode,  sizeof(szNode)))
                return NULL;
            break;
    }

    return szNode;
}