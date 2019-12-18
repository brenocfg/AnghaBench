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

__attribute__((used)) static void byteReverse(unsigned char *buf, unsigned longs) {
/* Forrest: MD5 expect LITTLE_ENDIAN, swap if BIG_ENDIAN */
#if BYTE_ORDER == BIG_ENDIAN
  do {
    uint32_t t = (uint32_t)((unsigned) buf[3] << 8 | buf[2]) << 16 |
                 ((unsigned) buf[1] << 8 | buf[0]);
    *(uint32_t *) buf = t;
    buf += 4;
  } while (--longs);
#else
  (void) buf;
  (void) longs;
#endif
}