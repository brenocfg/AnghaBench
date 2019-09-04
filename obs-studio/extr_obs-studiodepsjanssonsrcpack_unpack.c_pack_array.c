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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  scanner_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_array () ; 
 scalar_t__ json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_error (int /*<<< orphan*/ *,char*,char*) ; 
 char token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *pack_array(scanner_t *s, va_list *ap)
{
    json_t *array = json_array();
    next_token(s);

    while(token(s) != ']') {
        json_t *value;

        if(!token(s)) {
            set_error(s, "<format>", "Unexpected end of format string");
            goto error;
        }

        value = pack(s, ap);
        if(!value)
            goto error;

        if(json_array_append_new(array, value)) {
            set_error(s, "<internal>", "Unable to append to array");
            goto error;
        }

        next_token(s);
    }
    return array;

error:
    json_decref(array);
    return NULL;
}