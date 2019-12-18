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
struct TYPE_3__ {int /*<<< orphan*/  iSubItem; int /*<<< orphan*/  iItem; int /*<<< orphan*/  flags; int /*<<< orphan*/  pt; } ;
typedef  TYPE_1__ LVHITTESTINFO ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char* debuglvhittestinfo(const LVHITTESTINFO *lpht)
{
    if (!lpht) return "(null)";

    return wine_dbg_sprintf("{pt=%s, flags=0x%x, iItem=%d, iSubItem=%d}",
		 wine_dbgstr_point(&lpht->pt), lpht->flags, lpht->iItem, lpht->iSubItem);
}