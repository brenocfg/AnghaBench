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
typedef  size_t styleid_t ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMCSSStyleDeclaration ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMCSSStyleDeclaration_GetPropertyValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* style_tbl ; 

__attribute__((used)) static HRESULT get_nsstyle_attr_nsval(nsIDOMCSSStyleDeclaration *nsstyle, styleid_t sid, nsAString *value)
{
    nsAString str_name;
    nsresult nsres;

    nsAString_InitDepend(&str_name, style_tbl[sid].name);

    nsres = nsIDOMCSSStyleDeclaration_GetPropertyValue(nsstyle, &str_name, value);
    if(NS_FAILED(nsres)) {
        ERR("SetProperty failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsAString_Finish(&str_name);

    return NS_OK;
}