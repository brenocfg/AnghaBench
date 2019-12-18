#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char token; } ;
typedef  TYPE_1__ lex_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * json_array () ; 
 scalar_t__ json_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_scan (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_value (TYPE_1__*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *parse_array(lex_t *lex, size_t flags, json_error_t *error)
{
    json_t *array = json_array();
    if(!array)
        return NULL;

    lex_scan(lex, error);
    if(lex->token == ']')
        return array;

    while(lex->token) {
        json_t *elem = parse_value(lex, flags, error);
        if(!elem)
            goto error;

        if(json_array_append(array, elem)) {
            json_decref(elem);
            goto error;
        }
        json_decref(elem);

        lex_scan(lex, error);
        if(lex->token != ',')
            break;

        lex_scan(lex, error);
    }

    if(lex->token != ']') {
        error_set(error, lex, "']' expected");
        goto error;
    }

    return array;

error:
    json_decref(array);
    return NULL;
}