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
struct http_message {int dummy; } ;

/* Variables and functions */
 struct mg_str* mg_get_http_header (struct http_message*,char*) ; 
 int mg_parse_http_basic_auth (struct mg_str*,char*,size_t,char*,size_t) ; 

int mg_get_http_basic_auth(struct http_message *hm, char *user, size_t user_len,
                           char *pass, size_t pass_len) {
  struct mg_str *hdr = mg_get_http_header(hm, "Authorization");
  if (hdr == NULL) return -1;
  return mg_parse_http_basic_auth(hdr, user, user_len, pass, pass_len);
}