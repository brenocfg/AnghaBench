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
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {int /*<<< orphan*/  http_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ERR_ABRT ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  enduser_setup_http_recvcb ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  tcp_abort (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_accepted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_nagle_disable (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t enduser_setup_http_connectcb(void *arg, struct tcp_pcb *pcb, err_t err)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_connectcb");

  if (!state)
  {
    ENDUSER_SETUP_DEBUG("connect callback but no state?!");
    tcp_abort (pcb);
    return ERR_ABRT;
  }

  tcp_accepted (state->http_pcb);
  tcp_recv (pcb, enduser_setup_http_recvcb);
  tcp_nagle_disable (pcb);
  return ERR_OK;
}