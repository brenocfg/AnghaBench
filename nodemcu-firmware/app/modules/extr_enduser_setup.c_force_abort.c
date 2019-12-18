#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ERR_ABRT ; 
 int /*<<< orphan*/  tcp_abort (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t force_abort (void *arg, struct tcp_pcb *pcb)
{
  ENDUSER_SETUP_DEBUG("force_abort");

  (void)arg;
  tcp_poll (pcb, 0, 0);
  tcp_abort (pcb);
  return ERR_ABRT;
}