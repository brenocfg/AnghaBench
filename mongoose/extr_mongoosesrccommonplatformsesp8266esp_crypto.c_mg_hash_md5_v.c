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

/* Variables and functions */
 int /*<<< orphan*/  md5_vector (size_t,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ *) ; 

void mg_hash_md5_v(size_t num_msgs, const uint8_t *msgs[],
                   const size_t *msg_lens, uint8_t *digest) {
  (void) md5_vector(num_msgs, msgs, msg_lens, digest);
}