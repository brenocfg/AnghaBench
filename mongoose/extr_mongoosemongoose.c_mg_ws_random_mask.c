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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ rand () ; 

__attribute__((used)) static uint32_t mg_ws_random_mask(void) {
  uint32_t mask;
/*
 * The spec requires WS client to generate hard to
 * guess mask keys. From RFC6455, Section 5.3:
 *
 * The unpredictability of the masking key is essential to prevent
 * authors of malicious applications from selecting the bytes that appear on
 * the wire.
 *
 * Hence this feature is essential when the actual end user of this API
 * is untrusted code that wouldn't have access to a lower level net API
 * anyway (e.g. web browsers). Hence this feature is low prio for most
 * mongoose use cases and thus can be disabled, e.g. when porting to a platform
 * that lacks rand().
 */
#if MG_DISABLE_WS_RANDOM_MASK
  mask = 0xefbeadde; /* generated with a random number generator, I swear */
#else
  if (sizeof(long) >= 4) {
    mask = (uint32_t) rand();
  } else if (sizeof(long) == 2) {
    mask = (uint32_t) rand() << 16 | (uint32_t) rand();
  }
#endif
  return mask;
}