#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_4__ {int /*<<< orphan*/  json; scalar_t__ visited; int /*<<< orphan*/  hashtable; } ;
typedef  TYPE_1__ json_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_OBJECT ; 
 scalar_t__ hashtable_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashtable_seed ; 
 int /*<<< orphan*/  json_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_seed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonp_free (TYPE_1__*) ; 
 TYPE_1__* jsonp_malloc (int) ; 

json_t *json_object(void)
{
    json_object_t *object = jsonp_malloc(sizeof(json_object_t));
    if(!object)
        return NULL;

    if (!hashtable_seed) {
        /* Autoseed */
        json_object_seed(0);
    }

    json_init(&object->json, JSON_OBJECT);

    if(hashtable_init(&object->hashtable))
    {
        jsonp_free(object);
        return NULL;
    }

    object->visited = 0;

    return &object->json;
}