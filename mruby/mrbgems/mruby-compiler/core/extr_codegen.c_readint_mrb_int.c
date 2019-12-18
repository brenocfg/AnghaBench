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
typedef  int mrb_int ;
typedef  scalar_t__ mrb_bool ;
typedef  int /*<<< orphan*/  codegen_scope ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MRB_INT_MAX ; 
 int MRB_INT_MIN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  codegen_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 char* mrb_digitmap ; 
 int strlen (char const*) ; 
 char tolower (unsigned char) ; 

__attribute__((used)) static mrb_int
readint_mrb_int(codegen_scope *s, const char *p, int base, mrb_bool neg, mrb_bool *overflow)
{
  const char *e = p + strlen(p);
  mrb_int result = 0;
  int n;

  mrb_assert(base >= 2 && base <= 36);
  if (*p == '+') p++;
  while (p < e) {
    char c = *p;
    c = tolower((unsigned char)c);
    for (n=0; n<base; n++) {
      if (mrb_digitmap[n] == c) {
        break;
      }
    }
    if (n == base) {
      codegen_error(s, "malformed readint input");
    }

    if (neg) {
      if ((MRB_INT_MIN + n)/base > result) {
        *overflow = TRUE;
        return 0;
      }
      result *= base;
      result -= n;
    }
    else {
      if ((MRB_INT_MAX - n)/base < result) {
        *overflow = TRUE;
        return 0;
      }
      result *= base;
      result += n;
    }
    p++;
  }
  *overflow = FALSE;
  return result;
}