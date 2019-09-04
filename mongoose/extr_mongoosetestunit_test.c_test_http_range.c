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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char*,char*) ; 
 int FETCH_BUF_SIZE ; 
 int /*<<< orphan*/  fetch_http (char*,char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static const char *test_http_range(void) {
  char buf[FETCH_BUF_SIZE];

  fetch_http(buf, "%s", "GET /data/range.txt HTTP/1.0\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 200 OK");
  ASSERT(strstr(buf, "Content-Length: 312\r\n") != 0);

  /* Fetch a piece from the middle of the file */
  fetch_http(buf, "%s", "GET /data/range.txt HTTP/1.0\nRange: bytes=5-10\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 206 Partial Content");
  ASSERT(strstr(buf, "Content-Length: 6\r\n") != 0);
  ASSERT(strstr(buf, "Content-Range: bytes 5-10/312\r\n") != 0);
  ASSERT_STREQ(buf + strlen(buf) - 8, "\r\n of co");

  /* Fetch till EOF */
  fetch_http(buf, "%s", "GET /data/range.txt HTTP/1.0\nRange: bytes=300-\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 206 Partial Content");
  ASSERT(strstr(buf, "Content-Length: 12\r\n") != 0);
  ASSERT(strstr(buf, "Content-Range: bytes 300-311/312\r\n") != 0);
  ASSERT_STREQ(buf + strlen(buf) - 14, "\r\nis disease.\n");

  /* Fetch past EOF, must trigger 416 response */
  fetch_http(buf, "%s", "GET /data/range.txt HTTP/1.0\nRange: bytes=1000-\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 416");
  ASSERT(strstr(buf, "Content-Length: 0\r\n") != 0);
  ASSERT(strstr(buf, "Content-Range: bytes */312\r\n") != 0);

  /* Request range past EOF, must trigger 416 response */
  fetch_http(buf, "%s", "GET /data/range.txt HTTP/1.0\nRange: bytes=0-312\n\n");
  ASSERT_STREQ_NZ(buf, "HTTP/1.1 416");

  return NULL;
}