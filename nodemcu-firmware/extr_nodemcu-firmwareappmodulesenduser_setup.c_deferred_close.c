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

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  force_abort ; 
 int /*<<< orphan*/  handle_remote_close ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void deferred_close (struct tcp_pcb *pcb)
{
  ENDUSER_SETUP_DEBUG("deferred_close");

  tcp_poll (pcb, force_abort, 15); /* ~3sec from now */
  tcp_recv (pcb, handle_remote_close);
  tcp_sent (pcb, 0);
}