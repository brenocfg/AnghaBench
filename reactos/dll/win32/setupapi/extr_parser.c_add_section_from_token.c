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
struct parser {scalar_t__ token_len; int cur_section; int /*<<< orphan*/  error; int /*<<< orphan*/  file; int /*<<< orphan*/  token; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_SECTION_NAME_TOO_LONG ; 
 scalar_t__ MAX_SECTION_NAME_LEN ; 
 int add_section (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int find_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * push_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_section_from_token( struct parser *parser )
{
    int section_index;

    if (parser->token_len > MAX_SECTION_NAME_LEN)
    {
        parser->error = ERROR_SECTION_NAME_TOO_LONG;
        return -1;
    }
    if ((section_index = find_section( parser->file, parser->token )) == -1)
    {
        /* need to create a new one */
        const WCHAR *name = push_string( parser->file, parser->token );
        if ((section_index = add_section( parser->file, name )) == -1)
        {
            parser->error = ERROR_NOT_ENOUGH_MEMORY;
            return -1;
        }
    }
    parser->token_len = 0;
    parser->cur_section = section_index;
    return section_index;
}