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
struct parser {int /*<<< orphan*/ * hkey; int /*<<< orphan*/ * key_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_key(struct parser *parser)
{
    if (parser->hkey)
    {
        heap_free(parser->key_name);
        parser->key_name = NULL;

        RegCloseKey(parser->hkey);
        parser->hkey = NULL;
    }
}