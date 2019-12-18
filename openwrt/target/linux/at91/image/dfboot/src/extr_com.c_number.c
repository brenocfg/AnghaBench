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

/* Variables and functions */
 int LEFT ; 
 int SIGN ; 
 int ZEROPAD ; 
 size_t do_div (int,int) ; 
 int /*<<< orphan*/  putc (char) ; 

__attribute__((used)) static int number(int num, int base, int size,
                  int precision, int type)
{
  char c, sign, tmp[66];
  const char *digits="0123456789ABCDEF";
  int i;

  if (type & LEFT)
    type &= ~ZEROPAD;
  if (base < 2 || base > 16)
    return 0;
  c = (type & ZEROPAD) ? '0' : ' ';
  sign = 0;

  if(type & SIGN && num < 0)
    {
      sign = '-';
      num = -num;
      size--;
    }
  
  i = 0;
  if(num == 0)
    tmp[i++] = digits[0];
  else while(num != 0)
    tmp[i++] = digits[do_div(num, base)];

  if(i > precision)
    precision = i;
  size -= precision;
  
  if(!(type&(ZEROPAD+LEFT)))
    while(size-->0)
      putc(' ');
  
  if(sign)
    putc(sign);

  if (!(type & LEFT))
    while (size-- > 0)
      putc(c);

  while (i < precision--)
    putc('0');
  
  while (i-- > 0)
    putc(tmp[i]);

  while (size-- > 0)
    putc(' ');;

  return 1;
}