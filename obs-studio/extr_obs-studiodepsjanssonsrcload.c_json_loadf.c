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
typedef  int /*<<< orphan*/  lex_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;
typedef  int /*<<< orphan*/  get_func ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fgetc ; 
 int /*<<< orphan*/  jsonp_error_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lex_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_json (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 

json_t *json_loadf(FILE *input, size_t flags, json_error_t *error)
{
    lex_t lex;
    const char *source;
    json_t *result;

    if(input == stdin)
        source = "<stdin>";
    else
        source = "<stream>";

    jsonp_error_init(error, source);

    if (input == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    if(lex_init(&lex, (get_func)fgetc, flags, input))
        return NULL;

    result = parse_json(&lex, flags, error);

    lex_close(&lex);
    return result;
}