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
struct parser {int dummy; } ;
typedef  char WCHAR ;
typedef  scalar_t__ HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  RegDeleteTreeW (scalar_t__,char*) ; 
 int /*<<< orphan*/  close_key (struct parser*) ; 
 scalar_t__ parse_key_name (char*,char**) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *delete_key_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *p = pos;

    close_key(parser);

    if (*p == 'H' || *p == 'h')
    {
        HKEY root;
        WCHAR *path;

        root = parse_key_name(p, &path);

        if (root && path && *path)
            RegDeleteTreeW(root, path);
    }

    set_state(parser, LINE_START);
    return p;
}