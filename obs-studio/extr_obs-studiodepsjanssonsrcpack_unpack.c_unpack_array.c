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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ scanner_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int JSON_STRICT ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token (TYPE_1__*) ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,long) ; 
 long token (TYPE_1__*) ; 
 long type_name (int /*<<< orphan*/ *) ; 
 scalar_t__ unpack (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_value_starters ; 

__attribute__((used)) static int unpack_array(scanner_t *s, json_t *root, va_list *ap)
{
    size_t i = 0;
    int strict = 0;

    if(root && !json_is_array(root)) {
        set_error(s, "<validation>", "Expected array, got %s", type_name(root));
        return -1;
    }
    next_token(s);

    while(token(s) != ']') {
        json_t *value;

        if(strict != 0) {
            set_error(s, "<format>", "Expected ']' after '%c', got '%c'",
                      (strict == 1 ? '!' : '*'),
                      token(s));
            return -1;
        }

        if(!token(s)) {
            set_error(s, "<format>", "Unexpected end of format string");
            return -1;
        }

        if(token(s) == '!' || token(s) == '*') {
            strict = (token(s) == '!' ? 1 : -1);
            next_token(s);
            continue;
        }

        if(!strchr(unpack_value_starters, token(s))) {
            set_error(s, "<format>", "Unexpected format character '%c'",
                      token(s));
            return -1;
        }

        if(!root) {
            /* skipping */
            value = NULL;
        }
        else {
            value = json_array_get(root, i);
            if(!value) {
                set_error(s, "<validation>", "Array index %lu out of range",
                          (unsigned long)i);
                return -1;
            }
        }

        if(unpack(s, value, ap))
            return -1;

        next_token(s);
        i++;
    }

    if(strict == 0 && (s->flags & JSON_STRICT))
        strict = 1;

    if(root && strict == 1 && i != json_array_size(root)) {
        long diff = (long)json_array_size(root) - (long)i;
        set_error(s, "<validation>", "%li array item(s) left unpacked", diff);
        return -1;
    }

    return 0;
}