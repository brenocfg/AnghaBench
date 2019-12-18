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
struct parser {scalar_t__ parse_type; scalar_t__ data_size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ REG_BINARY ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_parser_data(struct parser *parser)
{
    if (parser->parse_type == REG_DWORD || parser->parse_type == REG_BINARY)
        heap_free(parser->data);

    parser->data = NULL;
    parser->data_size = 0;
}