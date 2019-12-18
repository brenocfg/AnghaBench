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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cs_sha1_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  cs_sha1_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_sha1_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

void mg_hash_sha1_v(size_t num_msgs, const uint8_t *msgs[],
                    const size_t *msg_lens, uint8_t *digest) {
  size_t i;
  cs_sha1_ctx sha_ctx;
  cs_sha1_init(&sha_ctx);
  for (i = 0; i < num_msgs; i++) {
    cs_sha1_update(&sha_ctx, msgs[i], msg_lens[i]);
  }
  cs_sha1_final(digest, &sha_ctx);
}