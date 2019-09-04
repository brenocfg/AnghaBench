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
struct mg_str {char* p; int len; } ;
struct mbuf {int dummy; } ;
struct cs_base64_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_base64_finish (struct cs_base64_ctx*) ; 
 int /*<<< orphan*/  cs_base64_init (struct cs_base64_ctx*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  cs_base64_update (struct cs_base64_ctx*,char*,int) ; 
 int /*<<< orphan*/  mbuf_append (struct mbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mbuf_append_base64_putc ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void mg_basic_auth_header(const struct mg_str user, const struct mg_str pass,
                          struct mbuf *buf) {
  const char *header_prefix = "Authorization: Basic ";
  const char *header_suffix = "\r\n";

  struct cs_base64_ctx ctx;
  cs_base64_init(&ctx, mg_mbuf_append_base64_putc, buf);

  mbuf_append(buf, header_prefix, strlen(header_prefix));

  cs_base64_update(&ctx, user.p, user.len);
  if (pass.len > 0) {
    cs_base64_update(&ctx, ":", 1);
    cs_base64_update(&ctx, pass.p, pass.len);
  }
  cs_base64_finish(&ctx);
  mbuf_append(buf, header_suffix, strlen(header_suffix));
}