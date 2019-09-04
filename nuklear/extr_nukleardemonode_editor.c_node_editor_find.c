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
struct node_editor {struct node* begin; } ;
struct node {int ID; struct node* next; } ;

/* Variables and functions */

__attribute__((used)) static struct node*
node_editor_find(struct node_editor *editor, int ID)
{
    struct node *iter = editor->begin;
    while (iter) {
        if (iter->ID == ID)
            return iter;
        iter = iter->next;
    }
    return NULL;
}