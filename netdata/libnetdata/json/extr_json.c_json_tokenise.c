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
typedef  int /*<<< orphan*/  jsmntok_t ;
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 int JSMN_ERROR_INVAL ; 
 int JSMN_ERROR_NOMEM ; 
 int JSMN_ERROR_PART ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ *,int) ; 
 int json_tokens ; 
 int /*<<< orphan*/ * mallocz (int) ; 
 int /*<<< orphan*/ * reallocz (int /*<<< orphan*/ *,int) ; 

jsmntok_t *json_tokenise(char *js, size_t len, size_t *count)
{
    int n = json_tokens;
    if(!js || !len) {
        error("JSON: json string is empty.");
        return NULL;
    }

    jsmn_parser parser;
    jsmn_init(&parser);

    jsmntok_t *tokens = mallocz(sizeof(jsmntok_t) * n);
    if(!tokens) return NULL;

    int ret = jsmn_parse(&parser, js, len, tokens, n);
    while (ret == JSMN_ERROR_NOMEM) {
        n *= 2;
        jsmntok_t *new = reallocz(tokens, sizeof(jsmntok_t) * n);
        if(!new) {
            freez(tokens);
            return NULL;
        }
        tokens = new;
        ret = jsmn_parse(&parser, js, len, tokens, n);
    }

    if (ret == JSMN_ERROR_INVAL) {
        error("JSON: Invalid json string.");
        freez(tokens);
        return NULL;
    }
    else if (ret == JSMN_ERROR_PART) {
        error("JSON: Truncated JSON string.");
        freez(tokens);
        return NULL;
    }

    if(count) *count = (size_t)ret;

    if(json_tokens < n) json_tokens = n;
    return tokens;
}