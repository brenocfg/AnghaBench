#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** playInterface; } ;
typedef  TYPE_1__ uri_player ;
struct TYPE_6__ {scalar_t__ (* SetPlayState ) (TYPE_2__**,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ SLresult ;
typedef  TYPE_2__** SLPlayItf ;

/* Variables and functions */
 int /*<<< orphan*/  SL_PLAYSTATE_PAUSED ; 
 scalar_t__ SL_RESULT_SUCCESS ; 
 scalar_t__ loop_start ; 
 scalar_t__ stub1 (TYPE_2__**,int /*<<< orphan*/ ) ; 

void slplay_stop(uri_player* player, char **error) {
  SLPlayItf playInterface = player->playInterface;
  SLresult result;

  // stop a loop
  loop_start = 0;

  result = (*playInterface)->SetPlayState(playInterface, SL_PLAYSTATE_PAUSED);
  if (result != SL_RESULT_SUCCESS) {
    *error = "Failed to set SL_PLAYSTATE_STOPPED";
    return;
  }
}