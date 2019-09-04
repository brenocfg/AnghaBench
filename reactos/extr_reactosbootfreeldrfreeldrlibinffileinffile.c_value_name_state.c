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
struct parser {int* start; } ;
typedef  int CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  COMMENT ; 
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  LEADING_SPACES ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  QUOTES ; 
 int /*<<< orphan*/  TRAILING_SPACES ; 
 int /*<<< orphan*/  VALUE_NAME ; 
 int /*<<< orphan*/  add_field_from_token (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_eol (struct parser*,int const*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  push_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_token (struct parser*,int const*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
const CHAR*
value_name_state(
    struct parser *parser,
    const CHAR *pos)
{
    const CHAR *p, *token_end = parser->start;

    for (p = pos; !is_eol(parser, p); p++)
    {
        switch(*p)
        {
        case ';':
            push_token(parser, token_end);
            if (!add_field_from_token(parser, 0)) return NULL;
            push_state(parser, LINE_START);
            set_state(parser, COMMENT);
            return p + 1;
        case ',':
            push_token(parser, token_end);
            if (!add_field_from_token(parser, 0)) return NULL;
            parser->start = p + 1;
            push_state(parser, VALUE_NAME);
            set_state(parser, LEADING_SPACES);
            return p + 1;
        case '"':
            push_token(parser, token_end);
            parser->start = p + 1;
            push_state(parser, VALUE_NAME);
            set_state(parser, QUOTES);
            return p + 1;
        case '\\':
            push_token(parser, token_end);
            parser->start = p;
            push_state(parser, VALUE_NAME);
            set_state(parser, EOL_BACKSLASH);
            return p;
        default:
            if (!isspace((unsigned char)*p)) token_end = p + 1;
            else
            {
                push_token(parser, p);
                push_state(parser, VALUE_NAME);
                set_state(parser, TRAILING_SPACES);
                return p;
            }
            break;
        }
    }
    push_token(parser, token_end);
    if (!add_field_from_token(parser, 0)) return NULL;
    set_state(parser, LINE_START);
    return p;
}