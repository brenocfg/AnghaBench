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
struct TYPE_3__ {int /*<<< orphan*/  hwndCombo; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  int /*<<< orphan*/  CBE_ITEMDATA ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline CBE_ITEMDATA *get_item_data(const COMBOEX_INFO *infoPtr, INT index)
{
    return (CBE_ITEMDATA *)SendMessageW (infoPtr->hwndCombo, CB_GETITEMDATA,
                                         index, 0);
}