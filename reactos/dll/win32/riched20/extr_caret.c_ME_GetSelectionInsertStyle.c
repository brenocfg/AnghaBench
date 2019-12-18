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
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;

/* Variables and functions */
 int /*<<< orphan*/ * ME_GetInsertStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ME_Style *ME_GetSelectionInsertStyle(ME_TextEditor *editor)
{
  return ME_GetInsertStyle(editor, 0);
}