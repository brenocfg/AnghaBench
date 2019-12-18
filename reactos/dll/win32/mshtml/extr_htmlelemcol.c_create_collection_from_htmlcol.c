#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLCollection ;
struct TYPE_2__ {size_t len; size_t size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ elem_vector_t ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  IHTMLElementCollection ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HTMLElementCollection_Create (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elem_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_GetLength (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_Item (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

IHTMLElementCollection *create_collection_from_htmlcol(HTMLDocumentNode *doc, nsIDOMHTMLCollection *nscol)
{
    UINT32 length = 0, i;
    elem_vector_t buf;
    HTMLDOMNode *node;
    HRESULT hres = S_OK;

    nsIDOMHTMLCollection_GetLength(nscol, &length);

    buf.len = buf.size = length;
    if(buf.len) {
        nsIDOMNode *nsnode;

        buf.buf = heap_alloc(buf.size*sizeof(HTMLElement*));

        for(i=0; i<length; i++) {
            nsIDOMHTMLCollection_Item(nscol, i, &nsnode);
            hres = get_node(doc, nsnode, TRUE, &node);
            nsIDOMNode_Release(nsnode);
            if(FAILED(hres))
                break;
            buf.buf[i] = elem_from_HTMLDOMNode(node);
        }
    }else {
        buf.buf = NULL;
    }

    if(FAILED(hres)) {
        heap_free(buf.buf);
        return NULL;
    }

    return HTMLElementCollection_Create(buf.buf, buf.len);
}