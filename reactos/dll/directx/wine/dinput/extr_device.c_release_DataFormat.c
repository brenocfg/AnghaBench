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
struct TYPE_4__ {int /*<<< orphan*/ * user_df; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * dt; } ;
typedef  TYPE_1__ DataFormat ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

void release_DataFormat(DataFormat * format)
{
    TRACE("Deleting DataFormat: %p\n", format);

    HeapFree(GetProcessHeap(), 0, format->dt);
    format->dt = NULL;
    HeapFree(GetProcessHeap(), 0, format->offsets);
    format->offsets = NULL;
    HeapFree(GetProcessHeap(), 0, format->user_df);
    format->user_df = NULL;
}