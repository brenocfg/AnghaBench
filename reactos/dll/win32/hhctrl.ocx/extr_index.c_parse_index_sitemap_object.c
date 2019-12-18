#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_15__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ strbuf_t ;
struct TYPE_17__ {TYPE_1__* pCHMInfo; } ;
struct TYPE_16__ {int itemFlags; void* items; scalar_t__ nItems; } ;
struct TYPE_14__ {int /*<<< orphan*/  codePage; } ;
typedef  TYPE_3__ IndexItem ;
typedef  TYPE_4__ HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_node_name (TYPE_2__*,TYPE_2__*) ; 
 void* heap_alloc_zero (int) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  parse_index_obj_node_param (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_2__*) ; 

__attribute__((used)) static IndexItem *parse_index_sitemap_object(HHInfo *info, stream_t *stream)
{
    strbuf_t node, node_name;
    IndexItem *item;

    strbuf_init(&node);
    strbuf_init(&node_name);

    item = heap_alloc_zero(sizeof(IndexItem));
    item->nItems = 0;
    item->items = heap_alloc_zero(0);
    item->itemFlags = 0x11;

    while(next_node(stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "param", -1)) {
            parse_index_obj_node_param(item, node.buf, info->pCHMInfo->codePage);
        }else if(!_strnicmp(node_name.buf, "/object", -1)) {
            break;
        }else {
            WARN("Unhandled tag! %s\n", node_name.buf);
        }

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&node_name);

    return item;
}