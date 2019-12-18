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
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMHTMLCollection ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  PropertyBag ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_prop (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetElementsByTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT fill_props(nsIDOMHTMLElement *nselem, PropertyBag *prop_bag)
{
    const PRUnichar *name, *value;
    nsAString name_str, value_str;
    nsIDOMHTMLCollection *params;
    nsIDOMHTMLElement *param_elem;
    UINT32 length, i;
    nsIDOMNode *nsnode;
    nsresult nsres;
    HRESULT hres = S_OK;

    static const PRUnichar nameW[] = {'n','a','m','e',0};
    static const PRUnichar paramW[] = {'p','a','r','a','m',0};
    static const PRUnichar valueW[] = {'v','a','l','u','e',0};

    nsAString_InitDepend(&name_str, paramW);
    nsres = nsIDOMHTMLElement_GetElementsByTagName(nselem, &name_str, &params);
    nsAString_Finish(&name_str);
    if(NS_FAILED(nsres))
        return E_FAIL;

    nsres = nsIDOMHTMLCollection_GetLength(params, &length);
    if(NS_FAILED(nsres))
        length = 0;

    for(i=0; i < length; i++) {
        nsres = nsIDOMHTMLCollection_Item(params, i, &nsnode);
        if(NS_FAILED(nsres)) {
            hres = E_FAIL;
            break;
        }

        nsres = nsIDOMNode_QueryInterface(nsnode, &IID_nsIDOMHTMLElement, (void**)&param_elem);
        nsIDOMNode_Release(nsnode);
        if(NS_FAILED(nsres)) {
            hres = E_FAIL;
            break;
        }

        nsres = get_elem_attr_value(param_elem, nameW, &name_str, &name);
        if(NS_SUCCEEDED(nsres)) {
            nsres = get_elem_attr_value(param_elem, valueW, &value_str, &value);
            if(NS_SUCCEEDED(nsres)) {
                hres = add_prop(prop_bag, name, value);
                nsAString_Finish(&value_str);
            }

            nsAString_Finish(&name_str);
        }

        nsIDOMHTMLElement_Release(param_elem);
        if(FAILED(hres))
            break;
        if(NS_FAILED(nsres)) {
            hres = E_FAIL;
            break;
        }
    }

    nsIDOMHTMLCollection_Release(params);
    return hres;
}