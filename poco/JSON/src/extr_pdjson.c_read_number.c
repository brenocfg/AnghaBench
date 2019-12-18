#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int (* get ) (TYPE_2__*) ;int (* peek ) (TYPE_2__*) ;} ;
struct TYPE_14__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;
typedef  enum json_type { ____Placeholder_json_type } json_type ;

/* Variables and functions */
 int JSON_ERROR ; 
 int JSON_NUMBER ; 
 scalar_t__ is_digit (int) ; 
 int /*<<< orphan*/  json_error (TYPE_1__*,char*,int) ; 
 scalar_t__ pushchar (TYPE_1__*,char) ; 
 scalar_t__ read_digits (TYPE_1__*) ; 
 int /*<<< orphan*/ * strchr (char*,int) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*) ; 
 int stub3 (TYPE_2__*) ; 
 int stub4 (TYPE_2__*) ; 
 int stub5 (TYPE_2__*) ; 
 int stub6 (TYPE_2__*) ; 
 int stub7 (TYPE_2__*) ; 
 int stub8 (TYPE_2__*) ; 

__attribute__((used)) static enum json_type
read_number(json_stream *json, int c)
{
    if (pushchar(json, c) != 0)
        return JSON_ERROR;
    if (c == '-') {
        c = json->source.get(&json->source);
        if (is_digit(c)) {
            return read_number(json, c);
        } else {
            json_error(json, "unexpected byte, '%c'", c);
        }
    } else if (strchr("123456789", c) != NULL) {
        c = json->source.peek(&json->source);
        if (is_digit(c)) {
            if (read_digits(json) != 0)
                return JSON_ERROR;
        }
    }
    /* Up to decimal or exponent has been read. */
    c = json->source.peek(&json->source);
    if (strchr(".eE", c) == NULL) {
        if (pushchar(json, '\0') != 0)
            return JSON_ERROR;
        else
            return JSON_NUMBER;
    }
    if (c == '.') {
        json->source.get(&json->source); // consume .
        if (pushchar(json, c) != 0)
            return JSON_ERROR;
        if (read_digits(json) != 0)
            return JSON_ERROR;
    }
    /* Check for exponent. */
    c = json->source.peek(&json->source);
    if (c == 'e' || c == 'E') {
        json->source.get(&json->source); // consume e/E
        if (pushchar(json, c) != 0)
            return JSON_ERROR;
        c = json->source.peek(&json->source);
        if (c == '+' || c == '-') {
            json->source.get(&json->source); // consume
            if (pushchar(json, c) != 0)
                return JSON_ERROR;
            if (read_digits(json) != 0)
                return JSON_ERROR;
        } else if (is_digit(c)) {
            if (read_digits(json) != 0)
                return JSON_ERROR;
        } else {
            json_error(json, "unexpected byte in number, '%c'", c);
            return JSON_ERROR;
        }
    }
    if (pushchar(json, '\0') != 0)
        return JSON_ERROR;
    else
        return JSON_NUMBER;
}