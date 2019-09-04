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
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ json_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int json_string_equal(json_t *string1, json_t *string2)
{
    json_string_t *s1, *s2;

    if(!json_is_string(string1) || !json_is_string(string2))
        return 0;

    s1 = json_to_string(string1);
    s2 = json_to_string(string2);
    return s1->length == s2->length && !memcmp(s1->value, s2->value, s1->length);
}