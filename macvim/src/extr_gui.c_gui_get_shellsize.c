#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num_cols; int /*<<< orphan*/  num_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  Columns ; 
 int OK ; 
 int /*<<< orphan*/  Rows ; 
 TYPE_1__ gui ; 

int
gui_get_shellsize()
{
    Rows = gui.num_rows;
    Columns = gui.num_cols;
    return OK;
}