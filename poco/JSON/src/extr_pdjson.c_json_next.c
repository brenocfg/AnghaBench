#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int (* peek ) (TYPE_3__*) ;int (* get ) (TYPE_3__*) ;} ;
struct TYPE_11__ {int flags; scalar_t__ next; scalar_t__ ntokens; size_t stack_top; TYPE_1__* stack; TYPE_3__ source; } ;
typedef  TYPE_2__ json_stream ;
typedef  enum json_type { ____Placeholder_json_type } json_type ;
struct TYPE_10__ {scalar_t__ type; int count; } ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ JSON_ARRAY ; 
 int JSON_DONE ; 
 int JSON_ERROR ; 
 int JSON_FLAG_ERROR ; 
 int JSON_FLAG_STREAMING ; 
 scalar_t__ JSON_OBJECT ; 
 int JSON_STRING ; 
 int /*<<< orphan*/  json_error (TYPE_2__*,char*,...) ; 
 scalar_t__ json_isspace (int) ; 
 int next (TYPE_2__*) ; 
 int pop (TYPE_2__*,int,scalar_t__) ; 
 int read_value (TYPE_2__*,int) ; 
 int stub1 (TYPE_3__*) ; 
 int stub2 (TYPE_3__*) ; 

enum json_type json_next(json_stream *json)
{
    if (json->flags & JSON_FLAG_ERROR)
        return JSON_ERROR;
    if (json->next != 0) {
        enum json_type next = json->next;
        json->next = (enum json_type) 0;
        return next;
    }
    if (json->ntokens > 0 && json->stack_top == (size_t)-1) {
        int c;

        do {
            c = json->source.peek(&json->source);
            if (json_isspace(c)) {
                c = json->source.get(&json->source);
            }
        } while (json_isspace(c));

        if (!(json->flags & JSON_FLAG_STREAMING) && c != EOF) {
            return JSON_ERROR;
        }

        return JSON_DONE;
    }
    int c = next(json);
    if (json->stack_top == (size_t)-1)
        return read_value(json, c);
    if (json->stack[json->stack_top].type == JSON_ARRAY) {
        if (json->stack[json->stack_top].count == 0) {
            if (c == ']') {
                return pop(json, c, JSON_ARRAY);
            }
            json->stack[json->stack_top].count++;
            return read_value(json, c);
        } else if (c == ',') {
            json->stack[json->stack_top].count++;
            return read_value(json, next(json));
        } else if (c == ']') {
            return pop(json, c, JSON_ARRAY);
        } else {
            json_error(json, "unexpected byte, '%c'", c);
            return JSON_ERROR;
        }
    } else if (json->stack[json->stack_top].type == JSON_OBJECT) {
        if (json->stack[json->stack_top].count == 0) {
            if (c == '}') {
                return pop(json, c, JSON_OBJECT);
            }

            /* No property value pairs yet. */
            enum json_type value = read_value(json, c);
            if (value != JSON_STRING) {
                json_error(json, "%s", "expected property name or '}'");
                return JSON_ERROR;
            } else {
                json->stack[json->stack_top].count++;
                return value;
            }
        } else if ((json->stack[json->stack_top].count % 2) == 0) {
            /* Expecting comma followed by property name. */
            if (c != ',' && c != '}') {
                json_error(json, "%s", "expected ',' or '}'");
                return JSON_ERROR;
            } else if (c == '}') {
                return pop(json, c, JSON_OBJECT);
            } else {
                enum json_type value = read_value(json, next(json));
                if (value != JSON_STRING) {
                    json_error(json, "%s", "expected property name");
                    return JSON_ERROR;
                } else {
                    json->stack[json->stack_top].count++;
                    return value;
                }
            }
        } else if ((json->stack[json->stack_top].count % 2) == 1) {
            /* Expecting colon followed by value. */
            if (c != ':') {
                json_error(json, "%s", "expected ':' after property name");
                return JSON_ERROR;
            } else {
                json->stack[json->stack_top].count++;
                return read_value(json, next(json));
            }
        }
    }
    json_error(json, "%s", "invalid parser state");
    return JSON_ERROR;
}