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
struct parser {int data_size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  SET_VALUE ; 
 int /*<<< orphan*/  convert_hex_to_dword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 int /*<<< orphan*/  heap_xalloc (int) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *dword_data_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *line = pos;

    parser->data = heap_xalloc(sizeof(DWORD));

    if (!convert_hex_to_dword(line, parser->data))
        goto invalid;

    parser->data_size = sizeof(DWORD);

    set_state(parser, SET_VALUE);
    return line;

invalid:
    free_parser_data(parser);
    set_state(parser, LINE_START);
    return line;
}