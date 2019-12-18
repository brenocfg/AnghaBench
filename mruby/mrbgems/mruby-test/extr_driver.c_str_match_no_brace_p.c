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
typedef  int mrb_bool ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 char const* UNESCAPE (char const*,char const*) ; 
 char* str_match_bracket (char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static mrb_bool
str_match_no_brace_p(const char *pat, mrb_int pat_len,
                     const char *str, mrb_int str_len)
{
  const char *p = pat, *s = str;
  const char *pat_end = pat + pat_len, *str_end = str + str_len;
  const char *p_tmp = NULL, *s_tmp = NULL;

  for (;;) {
    if (p == pat_end) return s == str_end;
    switch (*p) {
      case '*':
        do { ++p; } while (p != pat_end && *p == '*');
        if (UNESCAPE(p, pat_end) == pat_end) return TRUE;
        if (s == str_end) return FALSE;
        p_tmp = p;
        s_tmp = s;
        continue;
      case '?':
        if (s == str_end) return FALSE;
        ++p;
        ++s;
        continue;
      case '[': {
        const char *t;
        if (s == str_end) return FALSE;
        if ((t = str_match_bracket(p+1, pat_end, s, str_end))) {
          p = t;
          ++s;
          continue;
        }
        goto L_failed;
      }
    }

    /* ordinary */
    p = UNESCAPE(p, pat_end);
    if (s == str_end) return p == pat_end;
    if (p == pat_end) goto L_failed;
    if (*p++ != *s++) goto L_failed;
    continue;

    L_failed:
    if (p_tmp && s_tmp) {
      /* try next '*' position */
      p = p_tmp;
      s = ++s_tmp;
      continue;
    }

    return FALSE;
  }
}