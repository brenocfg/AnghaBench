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
struct mg_str {size_t len; scalar_t__ p; } ;
struct mbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned int MG_URL_ENCODE_F_SPACE_AS_PLUS ; 
 unsigned int MG_URL_ENCODE_F_UPPERCASE_HEX ; 
 scalar_t__ isalnum (unsigned char const) ; 
 int /*<<< orphan*/  mbuf_append (struct mbuf*,...) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,size_t) ; 
 int /*<<< orphan*/  mbuf_trim (struct mbuf*) ; 
 struct mg_str mg_mk_str_n (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * mg_strchr (struct mg_str const,unsigned char const) ; 

struct mg_str mg_url_encode_opt(const struct mg_str src,
                                const struct mg_str safe, unsigned int flags) {
  const char *hex =
      (flags & MG_URL_ENCODE_F_UPPERCASE_HEX ? "0123456789ABCDEF"
                                             : "0123456789abcdef");
  size_t i = 0;
  struct mbuf mb;
  mbuf_init(&mb, src.len);

  for (i = 0; i < src.len; i++) {
    const unsigned char c = *((const unsigned char *) src.p + i);
    if (isalnum(c) || mg_strchr(safe, c) != NULL) {
      mbuf_append(&mb, &c, 1);
    } else if (c == ' ' && (flags & MG_URL_ENCODE_F_SPACE_AS_PLUS)) {
      mbuf_append(&mb, "+", 1);
    } else {
      mbuf_append(&mb, "%", 1);
      mbuf_append(&mb, &hex[c >> 4], 1);
      mbuf_append(&mb, &hex[c & 15], 1);
    }
  }
  mbuf_append(&mb, "", 1);
  mbuf_trim(&mb);
  return mg_mk_str_n(mb.buf, mb.len - 1);
}