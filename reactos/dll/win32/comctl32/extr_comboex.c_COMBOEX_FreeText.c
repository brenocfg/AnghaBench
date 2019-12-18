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
struct TYPE_3__ {int /*<<< orphan*/ * pszTemp; int /*<<< orphan*/ * pszText; } ;
typedef  TYPE_1__ CBE_ITEMDATA ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_textW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void COMBOEX_FreeText (CBE_ITEMDATA *item)
{
    if (is_textW(item->pszText)) Free(item->pszText);
    item->pszText = NULL;
    Free(item->pszTemp);
    item->pszTemp = NULL;
}