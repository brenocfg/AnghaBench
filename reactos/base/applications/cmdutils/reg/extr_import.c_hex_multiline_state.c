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
struct parser {int /*<<< orphan*/  file; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  HEX_DATA ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  SET_VALUE ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 char* get_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isxdigitW (char) ; 
 int /*<<< orphan*/  prepare_hex_string_data (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *hex_multiline_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *line;

    if (!(line = get_line(parser->file)))
    {
        prepare_hex_string_data(parser);
        set_state(parser, SET_VALUE);
        return pos;
    }

    while (*line == ' ' || *line == '\t') line++;
    if (!*line || *line == ';') return line;

    if (!isxdigitW(*line)) goto invalid;

    set_state(parser, HEX_DATA);
    return line;

invalid:
    free_parser_data(parser);
    set_state(parser, LINE_START);
    return line;
}