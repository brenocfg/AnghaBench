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
struct TYPE_3__ {size_t Cols; int /*<<< orphan*/ ** Content; } ;
typedef  TYPE_1__ WhoamiTable ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;

/* Variables and functions */

void WhoamiSetTableDyn(WhoamiTable *pTable, WCHAR *Entry, UINT Row, UINT Col)
{
    pTable->Content[Row * pTable->Cols + Col] = Entry;
}