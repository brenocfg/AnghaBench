#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_GetTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL is_elem_tag(nsIDOMNode *node, LPCWSTR istag)
{
    nsIDOMElement *elem;
    nsAString tag_str;
    const PRUnichar *tag;
    BOOL ret = FALSE;
    nsresult nsres;

    nsres = nsIDOMNode_QueryInterface(node, &IID_nsIDOMElement, (void**)&elem);
    if(NS_FAILED(nsres))
        return FALSE;

    nsAString_Init(&tag_str, NULL);
    nsIDOMElement_GetTagName(elem, &tag_str);
    nsIDOMElement_Release(elem);
    nsAString_GetData(&tag_str, &tag);

    ret = !strcmpiW(tag, istag);

    nsAString_Finish(&tag_str);

    return ret;
}