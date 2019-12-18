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

/* Variables and functions */
 unsigned int PACK_FLAG_LSB ; 
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unpack_h(mrb_state *mrb, const void *src, int slen, mrb_value ary, int count, unsigned int flags)
{
  mrb_value dst;
  int a, ashift, b, bshift;
  const char *sptr, *sptr0;
  char *dptr, *dptr0;
  const char hexadecimal[] = "0123456789abcdef";

  if (flags & PACK_FLAG_LSB) {
    ashift = 0;
    bshift = 4;
  } else {
    ashift = 4;
    bshift = 0;
  }

  sptr = (const char *)src;

  if (count == -1)
    count = slen * 2;

  dst = mrb_str_new(mrb, NULL, count);
  dptr = RSTRING_PTR(dst);

  sptr0 = sptr;
  dptr0 = dptr;
  while (slen > 0 && count > 0) {
    a = (*sptr >> ashift) & 0x0f;
    b = (*sptr >> bshift) & 0x0f;
    sptr++;
    slen--;

    *dptr++ = hexadecimal[a];
    count--;

    if (count > 0) {
      *dptr++ = hexadecimal[b];
      count--;
    }
  }

  dst = mrb_str_resize(mrb, dst, dptr - dptr0);
  mrb_ary_push(mrb, ary, dst);
  return (int)(sptr - sptr0);
}