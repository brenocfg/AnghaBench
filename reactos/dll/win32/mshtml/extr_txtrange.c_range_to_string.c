#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int len; scalar_t__* buf; scalar_t__ size; } ;
typedef  TYPE_1__ wstrbuf_t ;
struct TYPE_18__ {scalar_t__ type; int off; int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ rangepoint_t ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ cpp_bool ;
typedef  scalar_t__ WCHAR ;
struct TYPE_19__ {int /*<<< orphan*/  nsrange; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_3__ HTMLTxtRange ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ TEXT_NODE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free_rangepoint (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_end_point (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_start_point (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_text_node_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ isspaceW (scalar_t__) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMRange_GetCollapsed (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rangepoint_cmp (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rangepoint_next_node (TYPE_2__*) ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wstrbuf_append_node (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstrbuf_append_nodetxt (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wstrbuf_finish (TYPE_1__*) ; 

__attribute__((used)) static void range_to_string(HTMLTxtRange *This, wstrbuf_t *buf)
{
    rangepoint_t end_pos, iter;
    cpp_bool collapsed;

    nsIDOMRange_GetCollapsed(This->nsrange, &collapsed);
    if(collapsed) {
        wstrbuf_finish(buf);
        buf->buf = NULL;
        buf->size = 0;
        return;
    }

    get_end_point(This, &end_pos);
    get_start_point(This, &iter);

    do {
        if(iter.type == TEXT_NODE) {
            const PRUnichar *str;
            nsAString nsstr;

            get_text_node_data(iter.node, &nsstr, &str);

            if(iter.node == end_pos.node) {
                wstrbuf_append_nodetxt(buf, str+iter.off, end_pos.off-iter.off);
                nsAString_Finish(&nsstr);
                break;
            }

            wstrbuf_append_nodetxt(buf, str+iter.off, strlenW(str+iter.off));
            nsAString_Finish(&nsstr);
        }else {
            nsIDOMNode *node;

            node = get_child_node(iter.node, iter.off);
            if(node) {
                wstrbuf_append_node(buf, node, TRUE);
                nsIDOMNode_Release(node);
            }
        }

        if(!rangepoint_next_node(&iter)) {
            ERR("End of document?\n");
            break;
        }
    }while(!rangepoint_cmp(&iter, &end_pos));

    free_rangepoint(&iter);
    free_rangepoint(&end_pos);

    if(buf->len) {
        WCHAR *p;

        for(p = buf->buf+buf->len-1; p >= buf->buf && isspaceW(*p); p--);

        p = strchrW(p, '\r');
        if(p)
            *p = 0;
    }
}