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
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_3__ {int /*<<< orphan*/  const* meth; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */

const UI_METHOD *UI_set_method(UI *ui, const UI_METHOD *meth)
{
    ui->meth = meth;
    return ui->meth;
}