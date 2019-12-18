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
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ json_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_stringn_nocheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* json_to_string (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static json_t *json_string_copy(const json_t *string)
{
    json_string_t *s;

    if(!json_is_string(string))
        return NULL;

    s = json_to_string(string);
    return json_stringn_nocheck(s->value, s->length);
}