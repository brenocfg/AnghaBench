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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ADDON_GECKO ; 
 int /*<<< orphan*/  ADDON_MONO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  install_addon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpW (char const*,char const*) ; 

__attribute__((used)) static LONG start_params(const WCHAR *params, HWND hwnd_parent)
{
    static const WCHAR install_geckoW[] = {'i','n','s','t','a','l','l','_','g','e','c','k','o',0};
    static const WCHAR install_monoW[] = {'i','n','s','t','a','l','l','_','m','o','n','o',0};

    if(!params)
        return FALSE;

    if(!strcmpW(params, install_geckoW)) {
        install_addon(ADDON_GECKO, hwnd_parent);
        return TRUE;
    }

    if(!strcmpW(params, install_monoW)) {
        install_addon(ADDON_MONO, hwnd_parent);
        return TRUE;
    }

    WARN("unknown param %s\n", debugstr_w(params));
    return FALSE;
}