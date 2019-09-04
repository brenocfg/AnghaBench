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
struct parser {char* data; int data_size; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  SET_VALUE ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unescape_string (char*,char**) ; 

__attribute__((used)) static WCHAR *string_data_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *line;

    parser->data = pos;

    if (!unescape_string(parser->data, &line))
        goto invalid;

    while (*line == ' ' || *line == '\t') line++;
    if (*line && *line != ';') goto invalid;

    parser->data_size = (lstrlenW(parser->data) + 1) * sizeof(WCHAR);

    set_state(parser, SET_VALUE);
    return line;

invalid:
    free_parser_data(parser);
    set_state(parser, LINE_START);
    return line;
}