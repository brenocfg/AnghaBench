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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ scan_listener_t ;
struct TYPE_5__ {TYPE_1__* scan_listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_2__* state ; 

__attribute__((used)) static void free_scan_listeners (void)
{
  ENDUSER_SETUP_DEBUG("free_scan_listeners");

  if (!state || !state->scan_listeners)
  {
    return;
  }

  scan_listener_t *l = state->scan_listeners , *next = 0;
  while (l)
  {
    next = l->next;
    free (l);
    l = next;
  }
  state->scan_listeners = 0;
}