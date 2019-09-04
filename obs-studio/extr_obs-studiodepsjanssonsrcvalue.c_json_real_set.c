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
struct TYPE_2__ {double value; } ;

/* Variables and functions */
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  json_is_real (int /*<<< orphan*/ *) ; 
 TYPE_1__* json_to_real (int /*<<< orphan*/ *) ; 

int json_real_set(json_t *json, double value)
{
    if(!json_is_real(json) || isnan(value) || isinf(value))
        return -1;

    json_to_real(json)->value = value;

    return 0;
}