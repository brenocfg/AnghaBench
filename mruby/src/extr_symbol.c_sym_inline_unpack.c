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
typedef  int mrb_sym ;
typedef  int mrb_int ;

/* Variables and functions */
 scalar_t__ SYMBOL_INLINE_LOWER_P (int) ; 
 int /*<<< orphan*/  SYMBOL_INLINE_P (int) ; 
 int SYMBOL_INLINE_SHIFT ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 char* pack_table ; 

__attribute__((used)) static const char*
sym_inline_unpack(mrb_sym sym, char *buf, mrb_int *lenp)
{
  int bit_per_char = SYMBOL_INLINE_LOWER_P(sym) ? 5 : 6;
  int i;

  mrb_assert(SYMBOL_INLINE_P(sym));

  for (i=0; i<30/bit_per_char; i++) {
    uint32_t bits = sym>>(i*bit_per_char+SYMBOL_INLINE_SHIFT) & ((1<<bit_per_char)-1);
    if (bits == 0) break;
    buf[i] = pack_table[bits-1];;
  }
  buf[i] = '\0';
  if (lenp) *lenp = i;
  return buf;
}