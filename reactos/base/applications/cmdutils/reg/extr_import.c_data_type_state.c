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
struct parser {int parse_type; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DWORD_DATA ; 
 int /*<<< orphan*/  HEX_DATA ; 
 int /*<<< orphan*/  LINE_START ; 
#define  REG_BINARY 130 
#define  REG_DWORD 129 
#define  REG_SZ 128 
 int /*<<< orphan*/  STRING_DATA ; 
 int /*<<< orphan*/  UNKNOWN_DATA ; 
 int /*<<< orphan*/  parse_data_type (struct parser*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *data_type_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *line = pos;

    if (!parse_data_type(parser, &line))
    {
        set_state(parser, LINE_START);
        return line;
    }

    switch (parser->parse_type)
    {
    case REG_SZ:
        set_state(parser, STRING_DATA);
        break;
    case REG_DWORD:
        set_state(parser, DWORD_DATA);
        break;
    case REG_BINARY: /* all hex data types, including undefined */
        set_state(parser, HEX_DATA);
        break;
    default:
        set_state(parser, UNKNOWN_DATA);
    }

    return line;
}