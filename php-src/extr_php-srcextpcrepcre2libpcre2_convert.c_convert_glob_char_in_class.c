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
typedef  int /*<<< orphan*/  PCRE2_UCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_HT ; 
 int /*<<< orphan*/  CHAR_SPACE ; 
 int /*<<< orphan*/  CHAR_UNDERSCORE ; 
 int isalnum (int /*<<< orphan*/ ) ; 
 int isalpha (int /*<<< orphan*/ ) ; 
 int iscntrl (int /*<<< orphan*/ ) ; 
 int isdigit (int /*<<< orphan*/ ) ; 
 int isgraph (int /*<<< orphan*/ ) ; 
 int islower (int /*<<< orphan*/ ) ; 
 int isprint (int /*<<< orphan*/ ) ; 
 int ispunct (int /*<<< orphan*/ ) ; 
 int isspace (int /*<<< orphan*/ ) ; 
 int isupper (int /*<<< orphan*/ ) ; 
 int isxdigit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
convert_glob_char_in_class(int class_index, PCRE2_UCHAR c)
{
switch (class_index)
  {
  case 1: return isalnum(c);
  case 2: return isalpha(c);
  case 3: return 1;
  case 4: return c == CHAR_HT || c == CHAR_SPACE;
  case 5: return iscntrl(c);
  case 6: return isdigit(c);
  case 7: return isgraph(c);
  case 8: return islower(c);
  case 9: return isprint(c);
  case 10: return ispunct(c);
  case 11: return isspace(c);
  case 12: return isupper(c);
  case 13: return isalnum(c) || c == CHAR_UNDERSCORE;
  default: return isxdigit(c);
  }
}