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
struct TYPE_2__ {int /*<<< orphan*/ * espconn_dns_udp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  espconn_delete (int /*<<< orphan*/ *) ; 
 TYPE_1__* state ; 

__attribute__((used)) static void enduser_setup_dns_stop(void)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_dns_stop");

  if (state != NULL && state->espconn_dns_udp != NULL)
  {
    espconn_delete(state->espconn_dns_udp);
  }
}