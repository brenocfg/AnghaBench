#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pressed; } ;
struct TYPE_4__ {TYPE_3__ event; } ;
typedef  TYPE_1__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  RaisePressed (TYPE_3__*,int) ; 
 int /*<<< orphan*/  RaiseReleased (int) ; 

bool RaiseSwitch ( keyrecord_t *record, bool *key_state, bool brother ){ 

  if( record -> event.pressed ) {
    *key_state = true;
    RaisePressed( &(record -> event), brother );
  } else {
    *key_state = false;
    RaiseReleased( brother );
  }
  return false;

}