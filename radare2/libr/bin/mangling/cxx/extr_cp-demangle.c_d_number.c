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
struct d_info {int dummy; } ;

/* Variables and functions */
 char INT_MAX ; 
 int /*<<< orphan*/  IS_DIGIT (char) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static int
d_number (struct d_info *di)
{
  int negative;
  char peek;
  int ret;

  negative = 0;
  peek = d_peek_char (di);
  if (peek == 'n')
    {
      negative = 1;
      d_advance (di, 1);
      peek = d_peek_char (di);
    }

  ret = 0;
  while (1)
    {
      if (! IS_DIGIT (peek))
	{
	  if (negative)
	    ret = - ret;
	  return ret;
	}
      if (ret > ((INT_MAX - (peek - '0')) / 10))
        return -1;
      ret = ret * 10 + peek - '0';
      d_advance (di, 1);
      peek = d_peek_char (di);
    }
}