#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* data; scalar_t__ pos; } ;
typedef  TYPE_1__ string_data_t ;
typedef  int /*<<< orphan*/  lex_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jsonp_error_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lex_close (int /*<<< orphan*/ *) ; 
 scalar_t__ lex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,void*) ; 
 int /*<<< orphan*/ * parse_json (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_get ; 

json_t *json_loads(const char *string, size_t flags, json_error_t *error)
{
    lex_t lex;
    json_t *result;
    string_data_t stream_data;

    jsonp_error_init(error, "<string>");

    if (string == NULL) {
        error_set(error, NULL, "wrong arguments");
        return NULL;
    }

    stream_data.data = string;
    stream_data.pos = 0;

    if(lex_init(&lex, string_get, flags, (void *)&stream_data))
        return NULL;

    result = parse_json(&lex, flags, error);

    lex_close(&lex);
    return result;
}