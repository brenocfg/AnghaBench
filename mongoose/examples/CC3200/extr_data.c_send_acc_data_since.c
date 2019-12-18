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
struct mg_connection {int dummy; } ;
struct bm222_sample {double ts; } ;
struct bm222_ctx {int last_index; struct bm222_sample* data; } ;

/* Variables and functions */
 int BM222_NUM_SAMPLES ; 
 int /*<<< orphan*/  send_acc_sample (struct mg_connection*,struct bm222_sample const*) ; 

__attribute__((used)) static double send_acc_data_since(struct mg_connection *nc,
                                  const struct bm222_ctx *ctx, double since) {
  int i = (ctx->last_index + 1) % BM222_NUM_SAMPLES, n = BM222_NUM_SAMPLES;
  double last_sent_ts = 0;
  for (; n > 0; i = (i + 1) % BM222_NUM_SAMPLES, n--) {
    const struct bm222_sample *s = ctx->data + i;
    if (s->ts <= since) continue;
    send_acc_sample(nc, s);
    last_sent_ts = s->ts;
  }
  return last_sent_ts;
}