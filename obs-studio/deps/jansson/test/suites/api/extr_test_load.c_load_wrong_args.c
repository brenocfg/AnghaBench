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
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/ * json_load_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_wrong_args()
{
    json_t *json;
    json_error_t error;

    json = json_loads(NULL, 0, &error);
    if (json)
        fail("json_loads should return NULL if the first argument is NULL");

    json = json_loadb(NULL, 0, 0, &error);
    if (json)
        fail("json_loadb should return NULL if the first argument is NULL");

    json = json_loadf(NULL, 0, &error);
    if (json)
        fail("json_loadf should return NULL if the first argument is NULL");

    json = json_load_file(NULL, 0, &error);
    if (json)
        fail("json_loadf should return NULL if the first argument is NULL");
}