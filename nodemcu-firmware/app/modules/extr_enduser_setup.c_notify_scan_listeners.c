#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ conn; struct TYPE_3__* next; } ;
typedef  TYPE_1__ scan_listener_t ;
struct TYPE_4__ {TYPE_1__* scan_listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  TCP_WRITE_FLAG_COPY ; 
 int /*<<< orphan*/  close_once_sent ; 
 int /*<<< orphan*/  free_scan_listeners () ; 
 TYPE_2__* state ; 
 int /*<<< orphan*/  tcp_abort (scalar_t__) ; 
 int /*<<< orphan*/  tcp_sent (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_write (scalar_t__,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void notify_scan_listeners (const char *payload, size_t sz)
{
  ENDUSER_SETUP_DEBUG("notify_scan_listeners");

  if (!state)
  {
    return;
  }

  for (scan_listener_t *l = state->scan_listeners; l; l = l->next)
  {
    if (tcp_write (l->conn, payload, sz, TCP_WRITE_FLAG_COPY) != ERR_OK)
    {
      ENDUSER_SETUP_DEBUG("failed to send wifi list");
      tcp_abort (l->conn);
    }
    else
      tcp_sent (l->conn, close_once_sent); /* TODO: time-out sends? */
    l->conn = 0;
  }

  free_scan_listeners ();
}