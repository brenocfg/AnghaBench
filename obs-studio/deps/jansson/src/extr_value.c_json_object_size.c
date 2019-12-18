#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_4__ {size_t size; } ;
struct TYPE_5__ {TYPE_1__ hashtable; } ;
typedef  TYPE_2__ json_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_object (int /*<<< orphan*/  const*) ; 
 TYPE_2__* json_to_object (int /*<<< orphan*/  const*) ; 

size_t json_object_size(const json_t *json)
{
    json_object_t *object;

    if(!json_is_object(json))
        return 0;

    object = json_to_object(json);
    return object->hashtable.size;
}