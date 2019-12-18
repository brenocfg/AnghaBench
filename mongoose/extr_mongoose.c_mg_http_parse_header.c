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

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (char*) ; 
 int mg_http_parse_header2 (struct mg_str*,char const*,char**,size_t) ; 

int mg_http_parse_header(struct mg_str *hdr, const char *var_name, char *buf,
                         size_t buf_size) {
  char *buf2 = buf;

  int len = mg_http_parse_header2(hdr, var_name, &buf2, buf_size);

  if (buf2 != buf) {
    /* Buffer was not enough and was reallocated: free it and just return 0 */
    MG_FREE(buf2);
    return 0;
  }

  return len;
}