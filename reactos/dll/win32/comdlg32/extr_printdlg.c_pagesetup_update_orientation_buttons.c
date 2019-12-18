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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CheckRadioButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DMORIENT_LANDSCAPE ; 
 scalar_t__ pagesetup_get_orientation (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rad1 ; 
 int /*<<< orphan*/  rad2 ; 

__attribute__((used)) static void pagesetup_update_orientation_buttons(HWND hDlg, const pagesetup_data *data)
{
    if (pagesetup_get_orientation(data) == DMORIENT_LANDSCAPE)
        CheckRadioButton(hDlg, rad1, rad2, rad2);
    else
        CheckRadioButton(hDlg, rad1, rad2, rad1);
}