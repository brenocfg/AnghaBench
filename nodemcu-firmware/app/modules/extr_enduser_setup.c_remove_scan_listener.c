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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ scan_listener_t ;
struct TYPE_6__ {TYPE_1__* scan_listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_2__* state ; 

__attribute__((used)) static void remove_scan_listener (scan_listener_t *l)
{
  ENDUSER_SETUP_DEBUG("remove_scan_listener");

  if (state)
  {
    scan_listener_t **sl = &state->scan_listeners;
    while (*sl)
    {
      /* Remove any and all references to the closed conn from the scan list */
      if (*sl == l)
      {
        *sl = l->next;
        free (l);
        /* No early exit to guard against multi-entry on list */
      }
      else
        sl = &(*sl)->next;
    }
  }
}