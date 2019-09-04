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
struct node_editor {int /*<<< orphan*/  show_grid; int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct node_editor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 int /*<<< orphan*/  nk_true ; 
 int /*<<< orphan*/  node_editor_add (struct node_editor*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  node_editor_link (struct node_editor*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
node_editor_init(struct node_editor *editor)
{
    memset(editor, 0, sizeof(*editor));
    editor->begin = NULL;
    editor->end = NULL;
    node_editor_add(editor, "Source", nk_rect(40, 10, 180, 220), nk_rgb(255, 0, 0), 0, 1);
    node_editor_add(editor, "Source", nk_rect(40, 260, 180, 220), nk_rgb(0, 255, 0), 0, 1);
    node_editor_add(editor, "Combine", nk_rect(400, 100, 180, 220), nk_rgb(0,0,255), 2, 2);
    node_editor_link(editor, 0, 0, 2, 0);
    node_editor_link(editor, 1, 0, 2, 1);
    editor->show_grid = nk_true;
}