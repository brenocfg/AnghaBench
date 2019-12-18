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
struct TYPE_6__ {int type; int off; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
typedef  char PRUnichar ;

/* Variables and functions */
#define  ELEMENT_NODE 129 
#define  TEXT_NODE 128 
 int /*<<< orphan*/  brW ; 
 int /*<<< orphan*/  free_rangepoint (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_text_node_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  hrW ; 
 int /*<<< orphan*/  init_rangepoint (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_elem_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isspaceW (char const) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ rangepoint_next_node (TYPE_1__*) ; 

__attribute__((used)) static WCHAR move_next_char(rangepoint_t *iter)
{
    rangepoint_t last_space;
    nsIDOMNode *node;
    WCHAR cspace = 0;
    const WCHAR *p;

    do {
        switch(iter->type) {
        case TEXT_NODE: {
            const PRUnichar *str;
            nsAString nsstr;
            WCHAR c;

            get_text_node_data(iter->node, &nsstr, &str);
            p = str+iter->off;
            if(!*p) {
                nsAString_Finish(&nsstr);
                break;
            }

            c = *p;
            if(isspaceW(c)) {
                while(isspaceW(*p))
                    p++;

                if(cspace)
                    free_rangepoint(&last_space);
                else
                    cspace = ' ';

                iter->off = p-str;
                c = *p;
                nsAString_Finish(&nsstr);
                if(!c) { /* continue to skip spaces */
                    init_rangepoint(&last_space, iter->node, iter->off);
                    break;
                }

                return cspace;
            }else {
                nsAString_Finish(&nsstr);
            }

            /* If we have a non-space char and we're skipping spaces, stop and return the last found space. */
            if(cspace) {
                free_rangepoint(iter);
                *iter = last_space;
                return cspace;
            }

            iter->off++;
            return c;
        }
        case ELEMENT_NODE:
            node = get_child_node(iter->node, iter->off);
            if(!node)
                break;

            if(is_elem_tag(node, brW)) {
                if(cspace) {
                    nsIDOMNode_Release(node);
                    free_rangepoint(iter);
                    *iter = last_space;
                    return cspace;
                }

                cspace = '\n';
                init_rangepoint(&last_space, iter->node, iter->off+1);
            }else if(is_elem_tag(node, hrW)) {
                nsIDOMNode_Release(node);
                if(cspace) {
                    free_rangepoint(iter);
                    *iter = last_space;
                    return cspace;
                }

                iter->off++;
                return '\n';
            }

            nsIDOMNode_Release(node);
        }
    }while(rangepoint_next_node(iter));

    return cspace;
}