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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcp_pcb {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_NONFATAL ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_UNKOWN_ERROR ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  TCP_WRITE_FLAG_COPY ; 
 int /*<<< orphan*/  deferred_close (struct tcp_pcb*) ; 
 scalar_t__ tcp_write (struct tcp_pcb*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enduser_setup_http_serve_header(struct tcp_pcb *http_client, const char *header, uint32_t header_len)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_serve_header");

  err_t err = tcp_write (http_client, header, header_len, TCP_WRITE_FLAG_COPY);
  if (err != ERR_OK)
  {
    deferred_close (http_client);
    ENDUSER_SETUP_ERROR("http_serve_header failed on tcp_write", ENDUSER_SETUP_ERR_UNKOWN_ERROR, ENDUSER_SETUP_ERR_NONFATAL);
  }

  return 0;
}