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
struct TYPE_3__ {int /*<<< orphan*/  json; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ json_integer_t ;
typedef  int /*<<< orphan*/  json_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_INTEGER ; 
 int /*<<< orphan*/  json_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* jsonp_malloc (int) ; 

json_t *json_integer(json_int_t value)
{
    json_integer_t *integer = jsonp_malloc(sizeof(json_integer_t));
    if(!integer)
        return NULL;
    json_init(&integer->json, JSON_INTEGER);

    integer->value = value;
    return &integer->json;
}