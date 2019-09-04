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
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_int_t ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_integer (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_integer (int /*<<< orphan*/ *) ; 

int json_integer_set(json_t *json, json_int_t value)
{
    if(!json_is_integer(json))
        return -1;

    json_to_integer(json)->value = value;

    return 0;
}