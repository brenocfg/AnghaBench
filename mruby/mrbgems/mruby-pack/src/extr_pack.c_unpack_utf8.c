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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 unsigned long utf8_to_uv (int /*<<< orphan*/ *,char const*,long*) ; 

__attribute__((used)) static int
unpack_utf8(mrb_state *mrb, const unsigned char * src, int srclen, mrb_value ary, unsigned int flags)
{
  unsigned long uv;
  long lenp = srclen;

  if (srclen == 0) {
    return 1;
  }
  uv = utf8_to_uv(mrb, (const char *)src, &lenp);
  mrb_ary_push(mrb, ary, mrb_fixnum_value((mrb_int)uv));
  return (int)lenp;
}