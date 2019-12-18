#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMComment ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_4__ {int /*<<< orphan*/  nsdoc; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMComment ; 
 int /*<<< orphan*/  NS_ERROR_FAILURE ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * handle_insert_comment (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMComment_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMComment_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISupports_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  replace_node_by_html (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nsresult run_insert_comment(HTMLDocumentNode *doc, nsISupports *comment_iface, nsISupports *arg2)
{
    const PRUnichar *comment;
    nsIDOMComment *nscomment;
    PRUnichar *replace_html;
    nsAString comment_str;
    nsresult nsres;

    nsres = nsISupports_QueryInterface(comment_iface, &IID_nsIDOMComment, (void**)&nscomment);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMComment iface:%08x\n", nsres);
        return nsres;
    }

    nsAString_Init(&comment_str, NULL);
    nsres = nsIDOMComment_GetData(nscomment, &comment_str);
    if(NS_FAILED(nsres))
        return nsres;

    nsAString_GetData(&comment_str, &comment);
    replace_html = handle_insert_comment(doc, comment);
    nsAString_Finish(&comment_str);

    if(replace_html) {
        HRESULT hres;

        hres = replace_node_by_html(doc->nsdoc, (nsIDOMNode*)nscomment, replace_html);
        heap_free(replace_html);
        if(FAILED(hres))
            nsres = NS_ERROR_FAILURE;
    }


    nsIDOMComment_Release(nscomment);
    return nsres;
}