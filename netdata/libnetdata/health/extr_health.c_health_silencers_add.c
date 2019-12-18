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
struct TYPE_5__ {TYPE_1__* silencers; } ;
struct TYPE_4__ {int /*<<< orphan*/  families; int /*<<< orphan*/  hosts; int /*<<< orphan*/  contexts; int /*<<< orphan*/  charts; int /*<<< orphan*/  alarms; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SILENCER ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* silencers ; 

void health_silencers_add(SILENCER *silencer) {
    // Add the created instance to the linked list in silencers
    silencer->next = silencers->silencers;
    silencers->silencers = silencer;
    debug(D_HEALTH, "HEALTH command API: Added silencer %s:%s:%s:%s:%s", silencer->alarms,
          silencer->charts, silencer->contexts, silencer->hosts, silencer->families
    );
}