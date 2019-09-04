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
typedef  int /*<<< orphan*/  cs_stat_t ;
struct TYPE_2__ {char* enable_directory_listing; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char*,char*) ; 
 int FETCH_BUF_SIZE ; 
 int /*<<< orphan*/  fetch_http (char*,char*,char*) ; 
 scalar_t__ mg_stat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 TYPE_1__ s_http_server_opts ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static const char *test_http_dav(void) {
  char buf[FETCH_BUF_SIZE];
  cs_stat_t st;

  remove("./data/dav/b.txt");
  rmdir("./data/dav/d");

  /* Test PROPFIND  */
  s_http_server_opts.enable_directory_listing = "yes";
  fetch_http(buf, "%s", "PROPFIND / HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 207");
  ASSERT(strstr(buf, "a.txt") != NULL);
  ASSERT(strstr(buf, "hidden_file.txt") == NULL);

  /* Test MKCOL */
  fetch_http(buf, "%s", "MKCOL /d HTTP/1.0\nContent-Length:5\n\n12345");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 415");
  fetch_http(buf, "%s", "MKCOL /d HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 201");
  fetch_http(buf, "%s", "MKCOL /d HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 405");
  fetch_http(buf, "%s", "MKCOL /x/d HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 409");

  /* Test PUT */
  fetch_http(buf, "%s", "PUT /b.txt HTTP/1.0\nContent-Length: 5\n\n12345");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 201");
  fetch_http(buf, "%s", "GET /data/dav/b.txt HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 200");
  ASSERT(strstr(buf, "Content-Length: 5\r\n") != 0);
  ASSERT_STREQ(buf + strlen(buf) - 7, "\r\n12345");

  /* Test DELETE */
  fetch_http(buf, "%s", "DELETE /b.txt HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 204");
  ASSERT(mg_stat("./data/dav/b.txt", &st) != 0);
  fetch_http(buf, "%s", "DELETE /d HTTP/1.0\n\n");
  ASSERT(mg_stat("./data/dav/d", &st) != 0);

  /* Non-existing file */
  fetch_http(buf, "%s", "PROPFIND /__blah.txt HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 404");

  return NULL;
}