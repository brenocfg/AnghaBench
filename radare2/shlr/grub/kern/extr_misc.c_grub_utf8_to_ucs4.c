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
typedef  int /*<<< orphan*/  grub_uint8_t ;
typedef  int grub_uint32_t ;
typedef  scalar_t__ grub_size_t ;

/* Variables and functions */

grub_size_t
grub_utf8_to_ucs4 (grub_uint32_t *dest, grub_size_t destsize,
		   const grub_uint8_t *src, grub_size_t srcsize,
		   const grub_uint8_t **srcend)
{
  grub_uint32_t *p = dest;
  int count = 0;
  grub_uint32_t code = 0;

  if (srcend)
    *srcend = src;

  while (srcsize && destsize)
    {
      grub_uint32_t c = *src++;
      if (srcsize != (grub_size_t)-1)
	srcsize--;
      if (count)
	{
	  if ((c & 0xc0) != 0x80)
	    {
	      /* invalid */
	      code = '?';
	      /* Character c may be valid, don't eat it.  */
	      src--;
	      if (srcsize != (grub_size_t)-1)
		srcsize++;
	      count = 0;
	    }
	  else
	    {
	      code <<= 6;
	      code |= (c & 0x3f);
	      count--;
	    }
	}
      else
	{
	  if (c == 0)
	    break;

	  if ((c & 0x80) == 0x00)
	    code = c;
	  else if ((c & 0xe0) == 0xc0)
	    {
	      count = 1;
	      code = c & 0x1f;
	    }
	  else if ((c & 0xf0) == 0xe0)
	    {
	      count = 2;
	      code = c & 0x0f;
	    }
	  else if ((c & 0xf8) == 0xf0)
	    {
	      count = 3;
	      code = c & 0x07;
	    }
	  else if ((c & 0xfc) == 0xf8)
	    {
	      count = 4;
	      code = c & 0x03;
	    }
	  else if ((c & 0xfe) == 0xfc)
	    {
	      count = 5;
	      code = c & 0x01;
	    }
	  else
	    {
	      /* invalid */
	      code = '?';
	      count = 0;
	    }
	}

      if (count == 0)
	{
	  *p++ = code;
	  destsize--;
	}
    }

  if (srcend)
    *srcend = src;
  return p - dest;
}