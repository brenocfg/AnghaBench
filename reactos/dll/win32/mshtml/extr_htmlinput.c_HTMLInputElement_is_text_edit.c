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
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  nsinput; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_1__ HTMLInputElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLInputElement_GetType (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static BOOL HTMLInputElement_is_text_edit(HTMLDOMNode *iface)
{
    HTMLInputElement *This = impl_from_HTMLDOMNode(iface);
    const PRUnichar *type;
    nsAString nsstr;
    nsresult nsres;
    BOOL ret = FALSE;

    static const WCHAR buttonW[] = {'b','u','t','t','o','n',0};
    static const WCHAR hiddenW[] = {'h','i','d','d','e','n',0};
    static const WCHAR passwordW[] = {'p','a','s','s','w','o','r','d',0};
    static const WCHAR resetW[] = {'r','e','s','e','t',0};
    static const WCHAR submitW[] = {'s','u','b','m','i','t',0};
    static const WCHAR textW[] = {'t','e','x','t',0};

    nsAString_Init(&nsstr, NULL);
    nsres = nsIDOMHTMLInputElement_GetType(This->nsinput, &nsstr);
    if(NS_SUCCEEDED(nsres)) {
        nsAString_GetData(&nsstr, &type);
        ret = !strcmpW(type, buttonW) || !strcmpW(type, hiddenW) || !strcmpW(type, passwordW)
            || !strcmpW(type, resetW) || !strcmpW(type, submitW) || !strcmpW(type, textW);
    }
    nsAString_Finish(&nsstr);
    return ret;
}