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
typedef  scalar_t__ err_t ;
struct TYPE_2__ {int /*<<< orphan*/ * http_payload_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_NONFATAL ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_UNKOWN_ERROR ; 
 int /*<<< orphan*/  enduser_setup_http_load_payload () ; 
 TYPE_1__* state ; 
 int /*<<< orphan*/  streamout_sent ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,void*) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 unsigned int tcp_sndbuf (struct tcp_pcb*) ; 
 scalar_t__ tcp_write (struct tcp_pcb*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enduser_setup_http_serve_html(struct tcp_pcb *http_client)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_serve_html");

  if (state->http_payload_data == NULL)
  {
    enduser_setup_http_load_payload();
  }

  unsigned chunklen = tcp_sndbuf (http_client);
  tcp_arg (http_client, (void *)chunklen);
  tcp_recv (http_client, 0); /* avoid confusion about the tcp_arg */
  tcp_sent (http_client, streamout_sent);
  /* Begin the no-copy stream-out here */
  err_t err = tcp_write (http_client, state->http_payload_data, chunklen, 0);
  if (err != 0)
  {
    ENDUSER_SETUP_ERROR("http_serve_html failed. tcp_write failed", ENDUSER_SETUP_ERR_UNKOWN_ERROR, ENDUSER_SETUP_ERR_NONFATAL);
  }

  return 0;
}