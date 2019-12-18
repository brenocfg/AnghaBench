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
struct pbuf {int /*<<< orphan*/  tot_len; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recved (struct tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t handle_remote_close (void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  ENDUSER_SETUP_DEBUG("handle_remote_close");

  (void)arg; (void)err;
  if (p) /* server sent us data, just ACK and move on */
  {
    tcp_recved (pcb, p->tot_len);
    pbuf_free (p);
  }
  else /* hey, remote end closed, we can do a soft close safely, yay! */
  {
    tcp_recv (pcb, 0);
    tcp_poll (pcb, 0, 0);
    tcp_close (pcb);
  }
  return ERR_OK;
}