#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {int /*<<< orphan*/  szUrl; int /*<<< orphan*/  szID; } ;
struct TYPE_11__ {TYPE_1__ Link; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_12__ {int iLink; scalar_t__* szUrl; scalar_t__* szID; scalar_t__ stateMask; scalar_t__ state; scalar_t__ mask; } ;
struct TYPE_15__ {TYPE_4__ hdr; TYPE_3__ item; } ;
struct TYPE_14__ {int /*<<< orphan*/  Notify; int /*<<< orphan*/  Self; } ;
typedef  TYPE_5__ SYSLINK_INFO ;
typedef  TYPE_6__ NMLINK ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_7__ DOC_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT SYSLINK_SendParentNotify (const SYSLINK_INFO *infoPtr, UINT code, const DOC_ITEM *Link, int iLink)
{
    NMLINK nml;

    nml.hdr.hwndFrom = infoPtr->Self;
    nml.hdr.idFrom = GetWindowLongPtrW(infoPtr->Self, GWLP_ID);
    nml.hdr.code = code;

    nml.item.mask = 0;
    nml.item.iLink = iLink;
    nml.item.state = 0;
    nml.item.stateMask = 0;
    if(Link->u.Link.szID)
    {
        lstrcpyW(nml.item.szID, Link->u.Link.szID);
    }
    else
    {
        nml.item.szID[0] = 0;
    }
    if(Link->u.Link.szUrl)
    {
        lstrcpyW(nml.item.szUrl, Link->u.Link.szUrl);
    }
    else
    {
        nml.item.szUrl[0] = 0;
    }

    return SendMessageW(infoPtr->Notify, WM_NOTIFY, nml.hdr.idFrom, (LPARAM)&nml);
}