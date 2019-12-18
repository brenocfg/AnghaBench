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
struct parser {int const* start; int /*<<< orphan*/  line_pos; } ;
typedef  int CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  COMMENT ; 
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  LEADING_SPACES ; 
 int /*<<< orphan*/  is_eof (struct parser*,int const*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  pop_state (struct parser*) ; 
 int /*<<< orphan*/  push_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_token (struct parser*,int const*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
const CHAR*
eol_backslash_state(
    struct parser *parser,
    const CHAR *pos )
{
    const CHAR *p;

    for (p = pos; !is_eof(parser, p); p++)
    {
        switch(*p)
        {
        case '\r':
            continue;

        case '\n':
            parser->line_pos++;
            parser->start = p + 1;
            set_state(parser, LEADING_SPACES);
            return p + 1;

        case '\\':
            continue;

        case ';':
            push_state(parser, EOL_BACKSLASH);
            set_state(parser, COMMENT);
            return p + 1;

        default:
            if (isspace((unsigned char)*p))
                continue;
            push_token(parser, p);
            pop_state(parser);
            return p;
        }
    }
    parser->start = p;
    pop_state(parser);

    return p;
}