#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  insert_type_t ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HHInfo ;
typedef  int /*<<< orphan*/  ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_CHILD ; 
 int /*<<< orphan*/  INSERT_NEXT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * insert_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * parse_ul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ContentItem *parse_hhc(HHInfo *info, IStream *str, ContentItem *hhc_root,
        insert_type_t *insert_type)
{
    stream_t stream;
    strbuf_t node, node_name;
    ContentItem *ret = NULL, *prev = NULL;

    *insert_type = INSERT_NEXT;

    strbuf_init(&node);
    strbuf_init(&node_name);

    stream_init(&stream, str);

    while(next_node(&stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "ul", -1)) {
            ContentItem *item = parse_ul(info, &stream, hhc_root);
            prev = insert_item(prev, item, INSERT_CHILD);
            if(!ret)
                ret = prev;
            *insert_type = INSERT_CHILD;
        }

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&node_name);

    return ret;
}