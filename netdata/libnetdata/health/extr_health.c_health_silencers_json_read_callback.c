#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int all_alarms; int /*<<< orphan*/  stype; } ;
struct TYPE_5__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int type; int (* callback_function ) (TYPE_2__*) ;TYPE_1__ data; int /*<<< orphan*/  name; int /*<<< orphan*/  callback_data; } ;
typedef  int /*<<< orphan*/  SILENCER ;
typedef  TYPE_2__ JSON_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
#define  JSON_ARRAY 133 
#define  JSON_BOOLEAN 132 
#define  JSON_NULL 131 
#define  JSON_NUMBER 130 
#define  JSON_OBJECT 129 
#define  JSON_STRING 128 
 int /*<<< orphan*/  STYPE_DISABLE_ALARMS ; 
 int /*<<< orphan*/  STYPE_SILENCE_NOTIFICATIONS ; 
 int /*<<< orphan*/  create_silencer () ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  health_silencers_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * health_silencers_addparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* silencers ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int health_silencers_json_read_callback(JSON_ENTRY *e)
{
    switch(e->type) {
        case JSON_OBJECT:
#ifndef ENABLE_JSONC
            e->callback_function = health_silencers_json_read_callback;
            if(strcmp(e->name,"")) {
                // init silencer
                debug(D_HEALTH, "JSON: Got object with a name, initializing new silencer for %s",e->name);
#endif
            e->callback_data = create_silencer();
            if(e->callback_data) {
                health_silencers_add(e->callback_data);
            }
#ifndef ENABLE_JSONC
            }
#endif
            break;

        case JSON_ARRAY:
            e->callback_function = health_silencers_json_read_callback;
            break;

        case JSON_STRING:
            if(!strcmp(e->name,"type")) {
                debug(D_HEALTH, "JSON: Processing type=%s",e->data.string);
                if (!strcmp(e->data.string,"SILENCE")) silencers->stype = STYPE_SILENCE_NOTIFICATIONS;
                else if (!strcmp(e->data.string,"DISABLE")) silencers->stype = STYPE_DISABLE_ALARMS;
            } else {
                debug(D_HEALTH, "JSON: Adding %s=%s", e->name, e->data.string);
                SILENCER *test = health_silencers_addparam(e->callback_data, e->name, e->data.string);
                (void)test;
            }
            break;

        case JSON_BOOLEAN:
            debug(D_HEALTH, "JSON: Processing all_alarms");
            silencers->all_alarms=e->data.boolean?1:0;
            break;

        case JSON_NUMBER:
        case JSON_NULL:
            break;
    }

    return 0;
}