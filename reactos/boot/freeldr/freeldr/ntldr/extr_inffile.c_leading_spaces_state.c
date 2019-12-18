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
struct parser {char const* start; } ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  is_eol (struct parser*,char const*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  pop_state (struct parser*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
const CHAR*
leading_spaces_state(
    struct parser *parser,
    const CHAR *pos )
{
    const CHAR *p;

    for (p = pos; !is_eol(parser, p); p++)
    {
        if (*p == '\\')
        {
            parser->start = p;
            set_state(parser, EOL_BACKSLASH);
            return p;
        }
        if (!isspace((unsigned char)*p))
            break;
    }
    parser->start = p;
    pop_state(parser);
    return p;
}