#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_17__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ strbuf_t ;
struct TYPE_18__ {int nItems; int indentLevel; struct TYPE_18__* next; int /*<<< orphan*/  merge; struct TYPE_18__* items; struct TYPE_18__* keyword; } ;
typedef  int /*<<< orphan*/  IndexSubItem ;
typedef  TYPE_2__ IndexItem ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  item_realloc (TYPE_2__*,int) ; 
 scalar_t__ lstrcmpW (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* parse_li (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_hhindex(HHInfo *info, IStream *str, IndexItem *item)
{
    stream_t stream;
    strbuf_t node, node_name;
    int indent_level = -1;

    strbuf_init(&node);
    strbuf_init(&node_name);

    stream_init(&stream, str);

    while(next_node(&stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "li", -1)) {
            IndexItem *new_item;

            new_item = parse_li(info, &stream);
            if(new_item && item->keyword && lstrcmpW(new_item->keyword, item->keyword) == 0) {
                int num_items = item->nItems;

                item_realloc(item, num_items+1);
                memcpy(&item->items[num_items], &new_item->items[0], sizeof(IndexSubItem));
                heap_free(new_item->keyword);
                heap_free(new_item->items);
                heap_free(new_item);
            } else if(new_item) {
                item->next = new_item;
                item->next->merge = item->merge;
                item = item->next;
                item->indentLevel = indent_level;
            }
        }else if(!_strnicmp(node_name.buf, "ul", -1)) {
            indent_level++;
        }else if(!_strnicmp(node_name.buf, "/ul", -1)) {
            indent_level--;
        }else {
            WARN("Unhandled tag! %s\n", node_name.buf);
        }

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&node_name);
}