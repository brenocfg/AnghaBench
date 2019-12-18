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
struct TYPE_3__ {int iString; scalar_t__ dwData; int /*<<< orphan*/  fsStyle; int /*<<< orphan*/  fsState; int /*<<< orphan*/  iBitmap; int /*<<< orphan*/  idCommand; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,char*) ; 
 char* debugstr_a (int /*<<< orphan*/ ) ; 
 char* debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TOOLBAR_DumpTBButton(const TBBUTTON *tbb, BOOL fUnicode)
{
    TRACE("TBBUTTON: id %d, bitmap=%d, state=%02x, style=%02x, data=%p, stringid=%p (%s)\n", tbb->idCommand,
        tbb->iBitmap, tbb->fsState, tbb->fsStyle, (void *)tbb->dwData, (void *)tbb->iString,
        tbb->iString != -1 ? (fUnicode ? debugstr_w((LPWSTR)tbb->iString) : debugstr_a((LPSTR)tbb->iString)) : "");
}