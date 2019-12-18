#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ jsmntok_t ;
struct TYPE_9__ {char* name; char* fullname; void* callback_data; int (* callback_function ) (struct json_entry*) ;int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ JSON_ENTRY ;

/* Variables and functions */
#define  JSMN_ARRAY 131 
#define  JSMN_OBJECT 130 
#define  JSMN_PRIMITIVE 129 
#define  JSMN_STRING 128 
 int /*<<< orphan*/  JSON_ARRAY ; 
 int /*<<< orphan*/  JSON_OBJECT ; 
 int /*<<< orphan*/  json_walk_array (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  json_walk_object (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

size_t json_walk_tree(char *js, jsmntok_t *t, void *callback_data, int (*callback_function)(struct json_entry *))
{
    JSON_ENTRY e = {
            .name = "",
            .fullname = "",
            .callback_data = callback_data,
            .callback_function = callback_function
    };

    switch (t[0].type) {
        case JSMN_OBJECT:
            e.type = JSON_OBJECT;
            json_walk_object(js, t, 0, 0, &e);
            break;

        case JSMN_ARRAY:
            e.type = JSON_ARRAY;
            json_walk_array(js, t, 0, 0, &e);
            break;

        case JSMN_PRIMITIVE:
        case JSMN_STRING:
            break;
    }

    return 1;
}