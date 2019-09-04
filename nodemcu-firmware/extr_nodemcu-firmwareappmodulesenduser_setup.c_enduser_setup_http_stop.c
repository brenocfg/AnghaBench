#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ http_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  tcp_close (scalar_t__) ; 

__attribute__((used)) static void enduser_setup_http_stop(void)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_stop");

  if (state && state->http_pcb)
  {
    tcp_close (state->http_pcb); /* cannot fail for listening sockets */
    state->http_pcb = 0;
  }
}