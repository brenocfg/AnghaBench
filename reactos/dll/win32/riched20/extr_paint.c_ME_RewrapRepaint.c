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

/* Variables and functions */
 int /*<<< orphan*/  ME_MarkAllForWrapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_Repaint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_UpdateScrollBar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_WrapMarkedParagraphs (int /*<<< orphan*/ *) ; 

void
ME_RewrapRepaint(ME_TextEditor *editor)
{
  /* RewrapRepaint should be called whenever the control has changed in
   * looks, but not content. Like resizing. */
  
  ME_MarkAllForWrapping(editor);
  ME_WrapMarkedParagraphs(editor);
  ME_UpdateScrollBar(editor);
  ME_Repaint(editor);
}