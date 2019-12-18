#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* child; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/  insert_content_item (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void fill_content_tree(HWND hwnd, ContentItem *parent, ContentItem *item)
{
    while(item) {
        if(item->name) {
            insert_content_item(hwnd, parent, item);
            fill_content_tree(hwnd, item, item->child);
        }else {
            fill_content_tree(hwnd, parent, item->child);
        }
        item = item->next;
    }
}