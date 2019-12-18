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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_AND_INC (char*,char const*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  str_match_no_brace_p (char const*,int,char const*,int) ; 

__attribute__((used)) static mrb_bool
str_match_p(mrb_state *mrb,
            const char *pat, mrb_int pat_len,
            const char *str, mrb_int str_len)
{
  const char *p = pat, *pat_end = pat + pat_len;
  const char *lbrace = NULL, *rbrace = NULL;
  int nest = 0;
  mrb_bool ret = FALSE;

  for (; p != pat_end; ++p) {
    if (*p == '{' && nest++ == 0) lbrace = p;
    else if (*p == '}' && lbrace && --nest == 0) { rbrace = p; break; }
    else if (*p == '\\' && ++p == pat_end) break;
  }

  if (lbrace && rbrace) {
    /* expand brace */
    char *ex_pat = (char *)mrb_malloc(mrb, pat_len-2);  /* expanded pattern */
    char *ex_p = ex_pat;

    COPY_AND_INC(ex_p, pat, lbrace-pat);
    p = lbrace;
    while (p < rbrace) {
      char *orig_ex_p = ex_p;
      const char *t = ++p;
      for (nest = 0; p < rbrace && !(*p == ',' && nest == 0); ++p) {
        if (*p == '{') ++nest;
        else if (*p == '}') --nest;
        else if (*p == '\\' && ++p == rbrace) break;
      }
      COPY_AND_INC(ex_p, t, p-t);
      COPY_AND_INC(ex_p, rbrace+1, pat_end-rbrace-1);
      if ((ret = str_match_p(mrb, ex_pat, ex_p-ex_pat, str, str_len))) break;
      ex_p = orig_ex_p;
    }
    mrb_free(mrb, ex_pat);
  }
  else if (!lbrace && !rbrace) {
    ret = str_match_no_brace_p(pat, pat_len, str, str_len);
  }

  return ret;
}