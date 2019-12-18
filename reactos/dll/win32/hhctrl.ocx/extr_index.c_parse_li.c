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
typedef  int /*<<< orphan*/  IndexItem ;
typedef  int /*<<< orphan*/  HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ ,char*,int) ; 
 char* get_attr (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * parse_index_sitemap_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 

__attribute__((used)) static IndexItem *parse_li(HHInfo *info, stream_t *stream)
{
    strbuf_t node, node_name;
    IndexItem *ret = NULL;

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
                ret = parse_index_sitemap_object(info, stream);
                break;
            }
        }else {
            WARN("Unhandled tag! %s\n", node_name.buf);
        }

        strbuf_zero(&node);
    }
    if(!ret)
        FIXME("Failed to parse <li> tag!\n");

    strbuf_free(&node);
    strbuf_free(&node_name);

    return ret;
}