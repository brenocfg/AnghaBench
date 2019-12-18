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
 int /*<<< orphan*/  enduser_setup_http_serve_header (struct tcp_pcb*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void enduser_setup_handle_OPTIONS (struct tcp_pcb *http_client, char *data, unsigned short data_len)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_handle_OPTIONS");

  const char json[] =
    "HTTP/1.1 200 OK\r\n"
    "Cache-Control: no-cache\r\n"
    "Connection: close\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: 0\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Access-Control-Allow-Methods: GET\r\n"
    "Access-Control-Allow-Age: 300\r\n"
    "\r\n";

  const char others[] =
    "HTTP/1.1 200 OK\r\n"
    "Cache-Control: no-cache\r\n"
    "Connection: close\r\n"
    "Content-Length: 0\r\n"
    "\r\n";

  int type = 0;

  if (strncmp(data, "GET ", 4) == 0)
  {
    if (strncmp(data + 4, "/aplist", 7) == 0 || strncmp(data + 4, "/setwifi?", 9) == 0 || strncmp(data + 4, "/status.json", 12) == 0)
    {
      enduser_setup_http_serve_header (http_client, json, strlen(json));
      return;
   }
  }
  enduser_setup_http_serve_header (http_client, others, strlen(others));
  return;
}