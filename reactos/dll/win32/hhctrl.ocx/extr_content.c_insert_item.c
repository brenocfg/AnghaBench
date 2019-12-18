#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int insert_type_t ;
struct TYPE_5__ {struct TYPE_5__* child; struct TYPE_5__* next; } ;
typedef  TYPE_1__ ContentItem ;

/* Variables and functions */
#define  INSERT_CHILD 129 
#define  INSERT_NEXT 128 

__attribute__((used)) static ContentItem *insert_item(ContentItem *item, ContentItem *new_item, insert_type_t insert_type)
{
    if(!item)
        return new_item;

    if(!new_item)
        return item;

    switch(insert_type) {
    case INSERT_NEXT:
        item->next = new_item;
        return new_item;
    case INSERT_CHILD:
        if(item->child) {
            ContentItem *iter = item->child;
            while(iter->next)
                iter = iter->next;
            iter->next = new_item;
        }else {
            item->child = new_item;
        }
        return item;
    }

    return NULL;
}