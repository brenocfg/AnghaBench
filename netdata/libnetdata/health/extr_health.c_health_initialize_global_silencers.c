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
struct TYPE_3__ {int /*<<< orphan*/ * silencers; int /*<<< orphan*/  stype; scalar_t__ all_alarms; } ;
typedef  int /*<<< orphan*/  SILENCERS ;

/* Variables and functions */
 int /*<<< orphan*/  STYPE_NONE ; 
 TYPE_1__* mallocz (int) ; 
 TYPE_1__* silencers ; 

int health_initialize_global_silencers() {
    silencers =  mallocz(sizeof(SILENCERS));
    silencers->all_alarms=0;
    silencers->stype=STYPE_NONE;
    silencers->silencers=NULL;

    return 0;
}