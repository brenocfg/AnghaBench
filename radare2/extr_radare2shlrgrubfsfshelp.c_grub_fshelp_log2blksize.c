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
 int /*<<< orphan*/  GRUB_ERR_BAD_NUMBER ; 
 unsigned int GRUB_ERR_NONE ; 
 unsigned int grub_error (int /*<<< orphan*/ ,char*) ; 

unsigned int
grub_fshelp_log2blksize (unsigned int blksize, unsigned int *pow)
{
  int mod;

  *pow = 0;
  while (blksize > 1)
    {
      mod = blksize - ((blksize >> 1) << 1);
      blksize >>= 1;

      /* Check if it really is a power of two.  */
      if (mod)
	return grub_error (GRUB_ERR_BAD_NUMBER,
			   "the blocksize is not a power of two");
      (*pow)++;
    }

  return GRUB_ERR_NONE;
}