#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pBuffer; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pCharStyle; } ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;

/* Variables and functions */
 int /*<<< orphan*/  ME_AddRefStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 

void ME_SaveTempStyle(ME_TextEditor *editor, ME_Style *style)
{
  ME_Style *old_style = editor->pBuffer->pCharStyle;

  if (style) ME_AddRefStyle( style );
  editor->pBuffer->pCharStyle = style;
  if (old_style) ME_ReleaseStyle( old_style );
}