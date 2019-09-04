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
 int /*<<< orphan*/  json_is_integer (int /*<<< orphan*/  const*) ; 
 TYPE_1__* json_to_integer (int /*<<< orphan*/  const*) ; 

json_int_t json_integer_value(const json_t *json)
{
    if(!json_is_integer(json))
        return 0;

    return json_to_integer(json)->value;
}