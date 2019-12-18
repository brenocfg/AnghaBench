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

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MAX_PATH ; 
 char const* backslashW ; 
 char* build_policy_name (char const*,char const*,char const*,unsigned int*) ; 
 scalar_t__ build_sxs_path (char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 scalar_t__ strlenW (char const*) ; 

__attribute__((used)) static WCHAR *build_policy_filename( const WCHAR *arch, const WCHAR *name, const WCHAR *token,
                                     const WCHAR *version )
{
    static const WCHAR policiesW[] = {'p','o','l','i','c','i','e','s','\\',0};
    static const WCHAR suffixW[] = {'.','p','o','l','i','c','y',0};
    WCHAR sxsdir[MAX_PATH], *ret, *fullname;
    unsigned int len;

    if (!(fullname = build_policy_name( arch, name, token, &len ))) return NULL;
    len += build_sxs_path( sxsdir );
    len += ARRAY_SIZE(policiesW) - 1;
    len += strlenW( version );
    len += ARRAY_SIZE(suffixW) - 1;
    if (!(ret = HeapAlloc( GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR) )))
    {
        HeapFree( GetProcessHeap(), 0, fullname );
        return NULL;
    }
    strcpyW( ret, sxsdir );
    strcatW( ret, policiesW );
    CreateDirectoryW( ret, NULL );
    strcatW( ret, name );
    CreateDirectoryW( ret, NULL );
    strcatW( ret, backslashW );
    strcatW( ret, version );
    strcatW( ret, suffixW );

    HeapFree( GetProcessHeap(), 0, fullname );
    return ret;
}