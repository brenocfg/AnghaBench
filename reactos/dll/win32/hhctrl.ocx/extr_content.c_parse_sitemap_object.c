#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_22__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  insert_type_t ;
struct TYPE_23__ {int /*<<< orphan*/  chm_file; scalar_t__ chm_index; } ;
struct TYPE_25__ {int /*<<< orphan*/  name; TYPE_20__ merge; int /*<<< orphan*/  child; } ;
struct TYPE_24__ {TYPE_19__* pCHMInfo; } ;
struct TYPE_21__ {int /*<<< orphan*/  codePage; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  TYPE_2__ HHInfo ;
typedef  TYPE_3__ ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/ * GetChmStream (TYPE_19__*,int /*<<< orphan*/ ,TYPE_20__*) ; 
 int /*<<< orphan*/  INSERT_NEXT ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_content_item (TYPE_3__*) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_hhc (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_obj_node_param (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 

__attribute__((used)) static ContentItem *parse_sitemap_object(HHInfo *info, stream_t *stream, ContentItem *hhc_root,
        insert_type_t *insert_type)
{
    strbuf_t node, node_name;
    ContentItem *item;

    *insert_type = INSERT_NEXT;

    strbuf_init(&node);
    strbuf_init(&node_name);

    item = heap_alloc_zero(sizeof(ContentItem));

    while(next_node(stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "/object", -1))
            break;
        if(!_strnicmp(node_name.buf, "param", -1))
            parse_obj_node_param(item, hhc_root, node.buf, info->pCHMInfo->codePage);

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&node_name);

    if(item->merge.chm_index) {
        IStream *merge_stream;

        merge_stream = GetChmStream(info->pCHMInfo, item->merge.chm_file, &item->merge);
        if(merge_stream) {
            item->child = parse_hhc(info, merge_stream, hhc_root, insert_type);
            IStream_Release(merge_stream);
        }else {
            WARN("Could not get %s::%s stream\n", debugstr_w(item->merge.chm_file),
                 debugstr_w(item->merge.chm_file));

            if(!item->name) {
                free_content_item(item);
                item = NULL;
            }
        }

    }

    return item;
}