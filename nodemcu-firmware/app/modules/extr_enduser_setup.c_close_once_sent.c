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
typedef  int /*<<< orphan*/  u16_t ;
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  deferred_close (struct tcp_pcb*) ; 

__attribute__((used)) static err_t close_once_sent (void *arg, struct tcp_pcb *pcb, u16_t len)
{
  ENDUSER_SETUP_DEBUG("close_once_sent");

  (void)arg; (void)len;
  deferred_close (pcb);
  return ERR_OK;
}