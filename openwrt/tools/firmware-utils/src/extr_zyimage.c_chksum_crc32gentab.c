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
 unsigned long* crc_tab ; 

void chksum_crc32gentab ()
{
  unsigned long crc, poly;
  int i, j;

  poly = 0xEDB88320L;
  for (i = 0; i < 256; i++)
  {
    crc = i;
    for (j = 8; j > 0; j--)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ poly;
      else
        crc >>= 1;
    }
    crc_tab[i] = crc;
  }
}