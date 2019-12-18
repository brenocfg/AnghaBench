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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SF_RTF ; 
 int /*<<< orphan*/  SF_TEXT ; 
 int /*<<< orphan*/  key_rtf ; 
 int /*<<< orphan*/  key_text ; 
 int /*<<< orphan*/  reg_formatindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_set_formatopts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void registry_set_formatopts_all(DWORD barState[], DWORD wordWrap[])
{
    registry_set_formatopts(reg_formatindex(SF_RTF), key_rtf, barState, wordWrap);
    registry_set_formatopts(reg_formatindex(SF_TEXT), key_text, barState, wordWrap);
}