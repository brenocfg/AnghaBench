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
struct mbuf {int dummy; } ;
struct cs_base64_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_base64_finish (struct cs_base64_ctx*) ; 
 int /*<<< orphan*/  cs_base64_init (struct cs_base64_ctx*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  cs_base64_update (struct cs_base64_ctx*,char const*,size_t) ; 
 int /*<<< orphan*/  mg_mbuf_append_base64_putc ; 

void mg_mbuf_append_base64(struct mbuf *mbuf, const void *data, size_t len) {
  struct cs_base64_ctx ctx;
  cs_base64_init(&ctx, mg_mbuf_append_base64_putc, mbuf);
  cs_base64_update(&ctx, (const char *) data, len);
  cs_base64_finish(&ctx);
}