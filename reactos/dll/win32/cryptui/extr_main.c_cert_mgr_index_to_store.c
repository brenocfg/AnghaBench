#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ TCITEMW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HCERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCIF_PARAM ; 
 int /*<<< orphan*/  TCM_GETITEMW ; 

__attribute__((used)) static HCERTSTORE cert_mgr_index_to_store(HWND tab, int index)
{
    TCITEMW item;

    item.mask = TCIF_PARAM;
    SendMessageW(tab, TCM_GETITEMW, index, (LPARAM)&item);
    return (HCERTSTORE)item.lParam;
}