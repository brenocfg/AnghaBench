#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  nselem; } ;
typedef  TYPE_1__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_SetAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT elem_string_attr_setter(HTMLElement *elem, const WCHAR *name, const WCHAR *value)
{
    nsAString name_str, val_str;
    nsresult nsres;

    nsAString_InitDepend(&name_str, name);
    nsAString_InitDepend(&val_str, value);
    nsres = nsIDOMHTMLElement_SetAttribute(elem->nselem, &name_str, &val_str);
    nsAString_Finish(&name_str);
    nsAString_Finish(&val_str);

    if(NS_FAILED(nsres)) {
        WARN("SetAttribute failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}