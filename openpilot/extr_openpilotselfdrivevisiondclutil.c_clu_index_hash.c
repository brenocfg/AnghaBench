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
typedef  scalar_t__ uint8_t ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t strlen (char const*) ; 

uint64_t clu_index_hash(const char* s) {
  size_t sl = strlen(s);
  assert(sl < 128);
  uint64_t x = 0;
  for (int i=127; i>=0; i--) {
    x *= 65599ULL;
    x += (uint8_t)s[i<sl ? sl-1-i : sl];
  }
  return x ^ (x >> 32);
}