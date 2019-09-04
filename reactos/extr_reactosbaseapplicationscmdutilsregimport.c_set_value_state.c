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
struct parser {scalar_t__ reg_version; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  data_type; int /*<<< orphan*/  value_name; int /*<<< orphan*/  hkey; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  PARSE_WIN31_LINE ; 
 scalar_t__ REG_VERSION_31 ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_parser_data (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *set_value_state(struct parser *parser, WCHAR *pos)
{
    RegSetValueExW(parser->hkey, parser->value_name, 0, parser->data_type,
                   parser->data, parser->data_size);

    free_parser_data(parser);

    if (parser->reg_version == REG_VERSION_31)
        set_state(parser, PARSE_WIN31_LINE);
    else
        set_state(parser, LINE_START);

    return pos;
}