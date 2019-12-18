#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ntokens; } ;
typedef  TYPE_1__ json_stream ;
typedef  enum json_type { ____Placeholder_json_type } json_type ;

/* Variables and functions */
#define  EOF 128 
 int /*<<< orphan*/  JSON_ARRAY ; 
 int JSON_ERROR ; 
 int /*<<< orphan*/  JSON_FALSE ; 
 int /*<<< orphan*/  JSON_NULL ; 
 int /*<<< orphan*/  JSON_OBJECT ; 
 int /*<<< orphan*/  JSON_TRUE ; 
 int /*<<< orphan*/  init_string (TYPE_1__*) ; 
 int is_match (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_error (TYPE_1__*,char*,...) ; 
 int push (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int read_number (TYPE_1__*,int) ; 
 int read_string (TYPE_1__*) ; 

__attribute__((used)) static enum json_type
read_value(json_stream *json, int c)
{
    json->ntokens++;
    switch (c) {
    case EOF:
        json_error(json, "%s", "unexpected end of data");
        return JSON_ERROR;
    case '{':
        return push(json, JSON_OBJECT);
    case '[':
        return push(json, JSON_ARRAY);
    case '"':
        return read_string(json);
    case 'n':
        return is_match(json, "ull", JSON_NULL);
    case 'f':
        return is_match(json, "alse", JSON_FALSE);
    case 't':
        return is_match(json, "rue", JSON_TRUE);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '-':
        if (init_string(json) != 0)
            return JSON_ERROR;
        return read_number(json, c);
    default:
        json_error(json, "unexpected byte, '%c'", c);
        return JSON_ERROR;
    }
}