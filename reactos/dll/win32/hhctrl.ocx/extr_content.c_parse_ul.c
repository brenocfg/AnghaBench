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
typedef  int /*<<< orphan*/  sz_text_sitemap ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  insert_type_t ;
typedef  int /*<<< orphan*/  HHInfo ;
typedef  int /*<<< orphan*/  ContentItem ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_CHILD ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 char* get_attr (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * insert_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * parse_sitemap_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 

__attribute__((used)) static ContentItem *parse_ul(HHInfo *info, stream_t *stream, ContentItem *hhc_root)
{
    strbuf_t node, node_name;
    ContentItem *ret = NULL, *prev = NULL, *new_item = NULL;
    insert_type_t it;

    strbuf_init(&node);
    strbuf_init(&node_name);

    while(next_node(stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "object", -1)) {
            const char *ptr;
            int len;

            static const char sz_text_sitemap[] = "text/sitemap";

            ptr = get_attr(node.buf, "type", &len);

            if(ptr && len == sizeof(sz_text_sitemap)-1
               && !memcmp(ptr, sz_text_sitemap, len)) {
                new_item = parse_sitemap_object(info, stream, hhc_root, &it);
                prev = insert_item(prev, new_item, it);
                if(!ret)
                    ret = prev;
            }
        }else if(!_strnicmp(node_name.buf, "ul", -1)) {
            new_item = parse_ul(info, stream, hhc_root);
            insert_item(prev, new_item, INSERT_CHILD);
        }else if(!_strnicmp(node_name.buf, "/ul", -1)) {
            break;
        }

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&node_name);

    return ret;
}