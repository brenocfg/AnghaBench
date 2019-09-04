#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer_value (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static json_t *json_integer_copy(const json_t *integer)
{
    return json_integer(json_integer_value(integer));
}