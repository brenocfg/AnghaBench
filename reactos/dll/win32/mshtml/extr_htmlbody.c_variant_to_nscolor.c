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
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VT_BSTR 129 
#define  VT_I4 128 
 int /*<<< orphan*/ * V_BSTR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/  const*) ; 
 int V_VT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

BOOL variant_to_nscolor(const VARIANT *v, nsAString *nsstr)
{
    switch(V_VT(v)) {
    case VT_BSTR:
        nsAString_Init(nsstr, V_BSTR(v));
        return TRUE;

    case VT_I4: {
        PRUnichar buf[10];
        static const WCHAR formatW[] = {'#','%','x',0};

        wsprintfW(buf, formatW, V_I4(v));
        nsAString_Init(nsstr, buf);
        return TRUE;
    }

    default:
        FIXME("invalid color %s\n", debugstr_variant(v));
    }

    return FALSE;

}