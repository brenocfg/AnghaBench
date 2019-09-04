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
struct mg_str {int dummy; } ;
struct altbuf {scalar_t__ len; } ;

/* Variables and functions */
 char* altbuf_get_buf (struct altbuf*,int) ; 
 int /*<<< orphan*/  altbuf_init (struct altbuf*,char*,size_t) ; 
 int /*<<< orphan*/  mg_http_parse_header_internal (struct mg_str*,char const*,struct altbuf*) ; 

int mg_http_parse_header2(struct mg_str *hdr, const char *var_name, char **buf,
                          size_t buf_size) {
  struct altbuf ab;
  altbuf_init(&ab, *buf, buf_size);
  if (hdr == NULL) return 0;
  if (*buf != NULL && buf_size > 0) *buf[0] = '\0';

  mg_http_parse_header_internal(hdr, var_name, &ab);

  /*
   * Get a (trimmed) buffer, and return a len without a NUL byte which might
   * have been added.
   */
  *buf = altbuf_get_buf(&ab, 1 /* trim */);
  return ab.len > 0 ? ab.len - 1 : 0;
}