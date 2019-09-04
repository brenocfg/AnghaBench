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
struct TYPE_2__ {char* extra_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int FETCH_BUF_SIZE ; 
 int /*<<< orphan*/  fetch_http (char*,char*,char*) ; 
 TYPE_1__ s_http_server_opts ; 
 int /*<<< orphan*/ * strstr (char*,char const*) ; 

__attribute__((used)) static const char *test_http_extra_headers(void) {
  char buf[FETCH_BUF_SIZE];
  const char *expect = "MyHdr: my_val\r\n";
  s_http_server_opts.extra_headers = "MyHdr: my_val";
  fetch_http(buf, "%s", "GET / HTTP/1.0\r\n\r\n");
  ASSERT(strstr(buf, expect) != NULL);
  s_http_server_opts.extra_headers = NULL;
  return NULL;
}