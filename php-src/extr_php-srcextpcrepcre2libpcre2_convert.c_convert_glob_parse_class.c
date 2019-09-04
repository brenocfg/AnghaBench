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
typedef  int /*<<< orphan*/  pcre2_output_context ;
typedef  scalar_t__ PCRE2_UCHAR ;
typedef  scalar_t__* PCRE2_SPTR ;

/* Variables and functions */
 scalar_t__ CHAR_COLON ; 
 char const CHAR_NUL ; 
 scalar_t__ CHAR_RIGHT_SQUARE_BRACKET ; 
 scalar_t__ CHAR_a ; 
 scalar_t__ CHAR_z ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  convert_glob_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
convert_glob_parse_class(PCRE2_SPTR *from, PCRE2_SPTR pattern_end,
  pcre2_output_context *out)
{
static const char *posix_classes = "alnum:alpha:ascii:blank:cntrl:digit:"
  "graph:lower:print:punct:space:upper:word:xdigit:";
PCRE2_SPTR start = *from + 1;
PCRE2_SPTR pattern = start;
const char *class_ptr;
PCRE2_UCHAR c;
int class_index;

while (TRUE)
  {
  if (pattern >= pattern_end) return 0;

  c = *pattern++;

  if (c < CHAR_a || c > CHAR_z) break;
  }

if (c != CHAR_COLON || pattern >= pattern_end ||
    *pattern != CHAR_RIGHT_SQUARE_BRACKET)
  return 0;

class_ptr = posix_classes;
class_index = 1;

while (TRUE)
  {
  if (*class_ptr == CHAR_NUL) return 0;

  pattern = start;

  while (*pattern == (PCRE2_UCHAR) *class_ptr)
    {
    if (*pattern == CHAR_COLON)
      {
      pattern += 2;
      start -= 2;

      do convert_glob_write(out, *start++); while (start < pattern);

      *from = pattern;
      return class_index;
      }
    pattern++;
    class_ptr++;
    }

  while (*class_ptr != CHAR_COLON) class_ptr++;
  class_ptr++;
  class_index++;
  }
}