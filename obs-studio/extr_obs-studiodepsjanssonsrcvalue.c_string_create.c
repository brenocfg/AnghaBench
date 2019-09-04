#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {char* value; size_t length; int /*<<< orphan*/  json; } ;
typedef  TYPE_1__ json_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_STRING ; 
 int /*<<< orphan*/  json_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonp_free (char*) ; 
 TYPE_1__* jsonp_malloc (int) ; 
 char* jsonp_strndup (char const*,size_t) ; 

__attribute__((used)) static json_t *string_create(const char *value, size_t len, int own)
{
    char *v;
    json_string_t *string;

    if(!value)
        return NULL;

    if(own)
        v = (char *)value;
    else {
        v = jsonp_strndup(value, len);
        if(!v)
            return NULL;
    }

    string = jsonp_malloc(sizeof(json_string_t));
    if(!string) {
        if(!own)
            jsonp_free(v);
        return NULL;
    }
    json_init(&string->json, JSON_STRING);
    string->value = v;
    string->length = len;

    return &string->json;
}