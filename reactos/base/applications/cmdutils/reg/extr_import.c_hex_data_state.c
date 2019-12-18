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
struct parser {scalar_t__ backslash; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  SET_VALUE ; 
 int /*<<< orphan*/  convert_hex_csv_to_hex (struct parser*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 int /*<<< orphan*/  prepare_hex_string_data (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *hex_data_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *line = pos;

    if (!*line)
        goto set_value;

    if (!convert_hex_csv_to_hex(parser, &line))
        goto invalid;

    if (parser->backslash)
    {
        set_state(parser, EOL_BACKSLASH);
        return line;
    }

    prepare_hex_string_data(parser);

set_value:
    set_state(parser, SET_VALUE);
    return line;

invalid:
    free_parser_data(parser);
    set_state(parser, LINE_START);
    return line;
}