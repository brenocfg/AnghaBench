#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__** player; int /*<<< orphan*/ * uri; } ;
typedef  TYPE_1__ uri_player ;
struct TYPE_11__ {int /*<<< orphan*/  (* Destroy ) (TYPE_4__**) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* Destroy ) (TYPE_3__**) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* Destroy ) (TYPE_2__**) ;} ;

/* Variables and functions */
 TYPE_2__** engine ; 
 TYPE_3__** outputMix ; 
 TYPE_1__* players ; 
 int /*<<< orphan*/  stub1 (TYPE_4__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**) ; 

void slplay_destroy() {
  for (uri_player *player = players; player->uri != NULL; player++) {
    if (player->player) {
      (*(player->player))->Destroy(player->player);
    }
  }

  (*outputMix)->Destroy(outputMix);
  (*engine)->Destroy(engine);
}