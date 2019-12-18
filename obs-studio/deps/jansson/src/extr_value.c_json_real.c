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
struct TYPE_3__ {double value; int /*<<< orphan*/  json; } ;
typedef  TYPE_1__ json_real_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_REAL ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  json_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* jsonp_malloc (int) ; 

json_t *json_real(double value)
{
    json_real_t *real;

    if(isnan(value) || isinf(value))
        return NULL;

    real = jsonp_malloc(sizeof(json_real_t));
    if(!real)
        return NULL;
    json_init(&real->json, JSON_REAL);

    real->value = value;
    return &real->json;
}