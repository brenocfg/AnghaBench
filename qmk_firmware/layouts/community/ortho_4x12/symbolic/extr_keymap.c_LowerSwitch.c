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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  LowerPressed (int) ; 
 int /*<<< orphan*/  LowerReleased (int) ; 

bool LowerSwitch ( keyrecord_t *record, bool *key_state, bool brother ){ 
  if ( record -> event.pressed ) {
    *key_state = true;
    LowerPressed( brother );
  } else {
    *key_state = false;
    LowerReleased( brother );
  }

  return false;

}