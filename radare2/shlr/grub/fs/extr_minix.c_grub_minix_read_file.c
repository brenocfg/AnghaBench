#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grub_minix_sblock {int dummy; } ;
struct grub_minix_data {TYPE_1__* disk; struct grub_minix_sblock sblock; } ;
typedef  int grub_ssize_t ;
typedef  scalar_t__ grub_disk_addr_t ;
struct TYPE_2__ {void (* read_hook ) (scalar_t__,unsigned int,unsigned int,void*) ;void* closure; } ;

/* Variables and functions */
 scalar_t__ GRUB_MINIX_BSIZE ; 
 scalar_t__ GRUB_MINIX_INODE_SIZE (struct grub_minix_data*) ; 
 int GRUB_MINIX_LOG2_ZONESZ ; 
 int /*<<< orphan*/  grub_disk_read (TYPE_1__*,int,int,int,char*) ; 
 scalar_t__ grub_errno ; 
 int grub_minix_get_file_block (struct grub_minix_data*,int) ; 

__attribute__((used)) static grub_ssize_t
grub_minix_read_file (struct grub_minix_data *data,
		      void (*read_hook) (grub_disk_addr_t sector,
					 unsigned offset, unsigned length,
					 void *closure),
		      void *closure,
		      int pos, grub_disk_addr_t len, char *buf)
{
  struct grub_minix_sblock *sblock = &data->sblock;
  int i;
  int blockcnt;

  /* Adjust len so it we can't read past the end of the file.  */
  if (len + pos > GRUB_MINIX_INODE_SIZE (data))
    len = GRUB_MINIX_INODE_SIZE (data) - pos;

  blockcnt = (len + pos + GRUB_MINIX_BSIZE - 1) / GRUB_MINIX_BSIZE;

  for (i = pos / GRUB_MINIX_BSIZE; i < blockcnt; i++)
    {
      int blknr;
      int blockoff = pos % GRUB_MINIX_BSIZE;
      int blockend = GRUB_MINIX_BSIZE;

      int skipfirst = 0;

      blknr = grub_minix_get_file_block (data, i);
      if (grub_errno)
	return -1;

      /* Last block.  */
      if (i == blockcnt - 1)
	{
	  blockend = (len + pos) % GRUB_MINIX_BSIZE;

	  if (!blockend)
	    blockend = GRUB_MINIX_BSIZE;
	}

      /* First block.  */
      if (i == (pos / (int) GRUB_MINIX_BSIZE))
	{
	  skipfirst = blockoff;
	  blockend -= skipfirst;
	}

      data->disk->read_hook = read_hook;
      data->disk->closure =  closure;
      grub_disk_read (data->disk, blknr << GRUB_MINIX_LOG2_ZONESZ,
		      skipfirst, blockend, buf);

      data->disk->read_hook = 0;
      if (grub_errno)
	return -1;

      buf += GRUB_MINIX_BSIZE - skipfirst;
    }

  return len;
}