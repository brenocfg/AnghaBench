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
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 unsigned int PACK_FLAG_LITTLEENDIAN ; 
 scalar_t__ littleendian ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static int
unpack_float(mrb_state *mrb, const unsigned char * src, int srclen, mrb_value ary, unsigned int flags)
{
  int i;
  float f;
  uint8_t *buffer = (uint8_t *)&f;

  if (flags & PACK_FLAG_LITTLEENDIAN) {
    if (littleendian) {
      memcpy(buffer, src, 4);
    }
    else {
      for (i = 0; i < 4; ++i) {
        buffer[4 - i - 1] = src[i];
      }
    }
  } else {
    if (littleendian) {
      for (i = 0; i < 4; ++i) {
        buffer[4 - i - 1] = src[i];
      }
    }
    else {
      memcpy(buffer, src, 4);
    }
  }
  mrb_ary_push(mrb, ary, mrb_float_value(mrb, f));

  return 4;
}