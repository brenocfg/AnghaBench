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
struct view {scalar_t__ proplist; } ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ SysStringLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_namespace (struct view const*) ; 
 int /*<<< orphan*/ * build_relpath (struct view const*,scalar_t__,char const*) ; 
 int /*<<< orphan*/ * build_servername (struct view const*) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlenW (char const*) ; 

__attribute__((used)) static BSTR build_path( const struct view *view, UINT index, const WCHAR *name )
{
    static const WCHAR fmtW[] = {'\\','\\','%','s','\\','%','s',':','%','s',0};
    BSTR server, namespace = NULL, relpath = NULL, ret = NULL;
    UINT len;

    if (view->proplist) return NULL;

    if (!(server = build_servername( view ))) return NULL;
    if (!(namespace = build_namespace( view ))) goto done;
    if (!(relpath = build_relpath( view, index, name ))) goto done;

    len = strlenW( fmtW ) + SysStringLen( server ) + SysStringLen( namespace ) + SysStringLen( relpath );
    if (!(ret = SysAllocStringLen( NULL, len ))) goto done;
    sprintfW( ret, fmtW, server, namespace, relpath );

done:
    SysFreeString( server );
    SysFreeString( namespace );
    SysFreeString( relpath );
    return ret;
}