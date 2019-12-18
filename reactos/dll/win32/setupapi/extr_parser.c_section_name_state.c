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
struct parser {int /*<<< orphan*/  error; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  COMMENT ; 
 int /*<<< orphan*/  ERROR_BAD_SECTION_NAME_LINE ; 
 int /*<<< orphan*/  LINE_START ; 
 int add_section_from_token (struct parser*) ; 
 int /*<<< orphan*/  is_eol (struct parser*,char const*) ; 
 int /*<<< orphan*/  push_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_token (struct parser*,char const*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *section_name_state( struct parser *parser, const WCHAR *pos )
{
    const WCHAR *p;

    for (p = pos; !is_eol( parser, p ); p++)
    {
        if (*p == ']')
        {
            push_token( parser, p );
            if (add_section_from_token( parser ) == -1) return NULL;
            push_state( parser, LINE_START );
            set_state( parser, COMMENT );  /* ignore everything else on the line */
            return p + 1;
        }
    }
    parser->error = ERROR_BAD_SECTION_NAME_LINE; /* unfinished section name */
    return NULL;
}