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
 int /*<<< orphan*/  STRING_ALIAS_NOT_FOUND ; 
 int /*<<< orphan*/  STRING_CMDLINE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  STRING_INVALID_PATH ; 
 int /*<<< orphan*/  WINE_FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* find_class (char*) ; 
 int /*<<< orphan*/  output_error (int /*<<< orphan*/ ) ; 
 int query_prop (char const*,char const*) ; 
 int /*<<< orphan*/  strcmpiW (char*,char const*) ; 

int wmain(int argc, WCHAR *argv[])
{
    static const WCHAR getW[] = {'g','e','t',0};
    static const WCHAR quitW[] = {'q','u','i','t',0};
    static const WCHAR exitW[] = {'e','x','i','t',0};
    static const WCHAR pathW[] = {'p','a','t','h',0};
    static const WCHAR classW[] = {'c','l','a','s','s',0};
    static const WCHAR contextW[] = {'c','o','n','t','e','x','t',0};
    const WCHAR *class, *value;
    int i;

    for (i = 1; i < argc && argv[i][0] == '/'; i++)
        WINE_FIXME( "command line switch %s not supported\n", debugstr_w(argv[i]) );

    if (i >= argc)
        goto not_supported;

    if (!strcmpiW( argv[i], quitW ) ||
        !strcmpiW( argv[i], exitW ))
    {
        return 0;
    }

    if (!strcmpiW( argv[i], classW) ||
        !strcmpiW( argv[i], contextW ))
    {
        WINE_FIXME( "command %s not supported\n", debugstr_w(argv[i]) );
        goto not_supported;
    }

    if (!strcmpiW( argv[i], pathW ))
    {
        if (++i >= argc)
        {
            output_error( STRING_INVALID_PATH );
            return 1;
        }
        class = argv[i];
    }
    else
    {
        class = find_class( argv[i] );
        if (!class)
        {
            output_error( STRING_ALIAS_NOT_FOUND );
            return 1;
        }
    }

    if (++i >= argc)
        goto not_supported;

    if (!strcmpiW( argv[i], getW ))
    {
        if (++i >= argc)
            goto not_supported;
        value = argv[i];
        return query_prop( class, value );
    }

not_supported:
    output_error( STRING_CMDLINE_NOT_SUPPORTED );
    return 1;
}