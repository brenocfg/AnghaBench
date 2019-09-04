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

/* Variables and functions */
 int /*<<< orphan*/  HEX_MULTILINE ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *eol_backslash_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *p = pos;

    while (*p == ' ' || *p == '\t') p++;
    if (*p && *p != ';') goto invalid;

    set_state(parser, HEX_MULTILINE);
    return pos;

invalid:
    free_parser_data(parser);
    set_state(parser, LINE_START);
    return p;
}