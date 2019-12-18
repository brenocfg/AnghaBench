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
 unsigned int Z_DEFLATED ; 
 int /*<<< orphan*/  put_byte (int /*<<< orphan*/ *,int,unsigned char) ; 

__attribute__((used)) static void write_zlib_header(uint8_t *s) {
  unsigned level_flags = 0; /* compression level (0..3) */
  unsigned w_bits = 8; /* window size log2(w_size)  (8..16) */
  unsigned int header = (Z_DEFLATED + ((w_bits-8)<<4)) << 8;
  header |= (level_flags << 6);

  header += 31 - (header % 31);

  /* s is guaranteed to be longer than 2 bytes. */
  put_byte(s, 0, (unsigned char)(header >> 8));
  put_byte(s, 1, (unsigned char)(header & 0xff));
}