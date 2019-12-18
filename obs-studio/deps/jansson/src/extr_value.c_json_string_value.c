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
struct TYPE_2__ {char const* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/  const*) ; 
 TYPE_1__* json_to_string (int /*<<< orphan*/  const*) ; 

const char *json_string_value(const json_t *json)
{
    if(!json_is_string(json))
        return NULL;

    return json_to_string(json)->value;
}