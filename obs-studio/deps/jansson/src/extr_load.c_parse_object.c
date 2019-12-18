#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char token; } ;
typedef  TYPE_1__ lex_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 size_t JSON_REJECT_DUPLICATES ; 
 char TOKEN_STRING ; 
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_set_nocheck (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonp_free (char*) ; 
 int /*<<< orphan*/  lex_scan (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* lex_steal_string (TYPE_1__*,size_t*) ; 
 scalar_t__ memchr (char*,char,size_t) ; 
 int /*<<< orphan*/ * parse_value (TYPE_1__*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *parse_object(lex_t *lex, size_t flags, json_error_t *error)
{
    json_t *object = json_object();
    if(!object)
        return NULL;

    lex_scan(lex, error);
    if(lex->token == '}')
        return object;

    while(1) {
        char *key;
        size_t len;
        json_t *value;

        if(lex->token != TOKEN_STRING) {
            error_set(error, lex, "string or '}' expected");
            goto error;
        }

        key = lex_steal_string(lex, &len);
        if(!key)
            return NULL;
        if (memchr(key, '\0', len)) {
            jsonp_free(key);
            error_set(error, lex, "NUL byte in object key not supported");
            goto error;
        }

        if(flags & JSON_REJECT_DUPLICATES) {
            if(json_object_get(object, key)) {
                jsonp_free(key);
                error_set(error, lex, "duplicate object key");
                goto error;
            }
        }

        lex_scan(lex, error);
        if(lex->token != ':') {
            jsonp_free(key);
            error_set(error, lex, "':' expected");
            goto error;
        }

        lex_scan(lex, error);
        value = parse_value(lex, flags, error);
        if(!value) {
            jsonp_free(key);
            goto error;
        }

        if(json_object_set_nocheck(object, key, value)) {
            jsonp_free(key);
            json_decref(value);
            goto error;
        }

        json_decref(value);
        jsonp_free(key);

        lex_scan(lex, error);
        if(lex->token != ',')
            break;

        lex_scan(lex, error);
    }

    if(lex->token != '}') {
        error_set(error, lex, "'}' expected");
        goto error;
    }

    return object;

error:
    json_decref(object);
    return NULL;
}