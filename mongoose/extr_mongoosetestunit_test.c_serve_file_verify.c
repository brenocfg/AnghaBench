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
struct mg_str {int dummy; } ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/  p; } ;
struct http_message {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_MG_STREQ (struct mg_str,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,size_t) ; 
 struct mg_str* mg_get_http_header (struct http_message*,char*) ; 
 char* read_file (char*,size_t*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *serve_file_verify(struct http_message *hm) {
  size_t size;
  char *data = read_file("unit_test.c", &size);
  if (data == NULL || size != hm->body.len ||
      memcmp(hm->body.p, data, size) != 0) {
    return "wrong data";
  }
  free(data);

  {
    char buf[20];
    struct mg_str *h = mg_get_http_header(hm, "Content-Length");
    ASSERT(h != NULL);
    snprintf(buf, sizeof(buf), "%d", (int) hm->body.len);
    ASSERT_MG_STREQ(*h, buf);
  }
  {
    struct mg_str *h = mg_get_http_header(hm, "Connection");
    ASSERT(h != NULL);
    ASSERT_MG_STREQ(*h, "keep-alive");
  }
  return "success";
}