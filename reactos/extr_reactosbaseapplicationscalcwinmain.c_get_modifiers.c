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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  IDC_CHECK_HYP ; 
 int /*<<< orphan*/  IDC_CHECK_INV ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MODIFIER_HYP ; 
 int MODIFIER_INV ; 

__attribute__((used)) static int get_modifiers(HWND hWnd)
{
    int modifiers = 0;

    if (IsDlgButtonChecked(hWnd, IDC_CHECK_INV) == BST_CHECKED)
        modifiers |= MODIFIER_INV;
    if (IsDlgButtonChecked(hWnd, IDC_CHECK_HYP) == BST_CHECKED)
        modifiers |= MODIFIER_HYP;

    return modifiers;
}