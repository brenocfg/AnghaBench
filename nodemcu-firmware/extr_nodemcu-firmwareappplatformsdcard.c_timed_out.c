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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ target; } ;
typedef  TYPE_1__ to_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ system_get_time () ; 

__attribute__((used)) static uint8_t timed_out( to_t *to )
{
  uint32_t now = system_get_time();

  if (to->start < to->target) {
    if ((now >= to->start) && (now <= to->target)) {
      return FALSE;
    } else {
      return TRUE;
    }
  } else {
    if ((now >= to->start) || (now <= to->target)) {
      return FALSE;
    } else {
      return TRUE;
    }
  }
}