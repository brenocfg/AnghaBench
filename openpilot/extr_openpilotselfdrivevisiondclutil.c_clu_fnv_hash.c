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
typedef  int uint64_t ;

/* Variables and functions */

uint64_t clu_fnv_hash(const uint8_t *data, size_t len) {
  /* 64 bit Fowler/Noll/Vo FNV-1a hash code */
  uint64_t hval = 0xcbf29ce484222325ULL;
  const uint8_t *dp = data;
  const uint8_t *de = data + len;
  while (dp < de) {
    hval ^= (uint64_t) *dp++;
    hval += (hval << 1) + (hval << 4) + (hval << 5) +
        (hval << 7) + (hval << 8) + (hval << 40);
  }

  return hval;
}