#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nPos; } ;
struct TYPE_6__ {TYPE_1__ horz_si; } ;
typedef  TYPE_2__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  ME_ScrollAbs (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void ME_VScrollAbs(ME_TextEditor *editor, int y)
{
  ME_ScrollAbs(editor, editor->horz_si.nPos, y);
}