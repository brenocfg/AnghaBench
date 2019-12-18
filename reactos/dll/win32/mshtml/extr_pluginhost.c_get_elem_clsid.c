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
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_classid (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL get_elem_clsid(nsIDOMHTMLElement *elem, CLSID *clsid)
{
    const PRUnichar *val;
    nsAString val_str;
    nsresult nsres;
    BOOL ret = FALSE;

    static const PRUnichar classidW[] = {'c','l','a','s','s','i','d',0};

    nsres = get_elem_attr_value(elem, classidW, &val_str, &val);
    if(NS_SUCCEEDED(nsres)) {
        if(*val)
            ret = parse_classid(val, clsid);
        nsAString_Finish(&val_str);
    }

    return ret;
}