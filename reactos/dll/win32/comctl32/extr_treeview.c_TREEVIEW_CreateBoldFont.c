#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  font ;
struct TYPE_4__ {int /*<<< orphan*/  lfWeight; } ;
typedef  TYPE_1__ LOGFONTW ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFontIndirectW (TYPE_1__*) ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static HFONT
TREEVIEW_CreateBoldFont(HFONT hOrigFont)
{
    LOGFONTW font;

    GetObjectW(hOrigFont, sizeof(font), &font);
    font.lfWeight = FW_BOLD;
    return CreateFontIndirectW(&font);
}