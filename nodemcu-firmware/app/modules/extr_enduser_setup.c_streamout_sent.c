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
typedef  int /*<<< orphan*/  u16_t ;
struct tcp_pcb {int dummy; } ;
typedef  scalar_t__ err_t ;
struct TYPE_2__ {unsigned int http_payload_len; scalar_t__ http_payload_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 scalar_t__ ERR_ABRT ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  deferred_close (struct tcp_pcb*) ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  tcp_abort (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,void*) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 unsigned int tcp_sndbuf (struct tcp_pcb*) ; 
 scalar_t__ tcp_write (struct tcp_pcb*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t streamout_sent (void *arg, struct tcp_pcb *pcb, u16_t len)
{
  ENDUSER_SETUP_DEBUG("streamout_sent");

  (void)len;
  unsigned offs = (unsigned)arg;

  if (!state || !state->http_payload_data)
  {
    tcp_abort (pcb);
    return ERR_ABRT;
  }

  unsigned wanted_len = state->http_payload_len - offs;
  unsigned buf_free = tcp_sndbuf (pcb);
  if (buf_free < wanted_len)
    wanted_len = buf_free;

  /* no-copy write */
  err_t err = tcp_write (pcb, state->http_payload_data + offs, wanted_len, 0);
  if (err != ERR_OK)
  {
    ENDUSER_SETUP_DEBUG("streaming out html failed");
    tcp_abort (pcb);
    return ERR_ABRT;
  }

  offs += wanted_len;

  if (offs >= state->http_payload_len)
  {
    tcp_sent (pcb, 0);
    deferred_close (pcb);
  }
  else
    tcp_arg (pcb, (void *)offs);

  return ERR_OK;
}