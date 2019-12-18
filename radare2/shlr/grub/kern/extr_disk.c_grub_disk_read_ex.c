#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int grub_size_t ;
typedef  unsigned int grub_off_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_2__* grub_disk_t ;
typedef  scalar_t__ grub_disk_addr_t ;
struct TYPE_9__ {int /*<<< orphan*/  closure; int /*<<< orphan*/  (* read_hook ) (scalar_t__,unsigned int,int,int /*<<< orphan*/ ) ;TYPE_1__* dev; } ;
struct TYPE_8__ {scalar_t__ (* read ) (TYPE_2__*,scalar_t__,int,char*) ;} ;

/* Variables and functions */
 int GRUB_DISK_SECTOR_BITS ; 
 int GRUB_DISK_SECTOR_SIZE ; 
 scalar_t__ GRUB_ERR_NONE ; 
 scalar_t__ grub_disk_adjust_range (TYPE_2__*,scalar_t__*,unsigned int*,int) ; 
 int /*<<< orphan*/  grub_disk_read (TYPE_2__*,scalar_t__,unsigned int,int,void*) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_memcpy (void*,char*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_2__*,scalar_t__,int,void*) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,unsigned int,int,int /*<<< orphan*/ ) ; 

grub_err_t
grub_disk_read_ex (grub_disk_t disk, grub_disk_addr_t sector,
		   grub_off_t offset, grub_size_t size, void *buf, int flags)
{
  unsigned real_offset;

  if (! flags)
    return grub_disk_read (disk, sector, offset, size, buf);

  if (grub_disk_adjust_range (disk, &sector, &offset, size) != GRUB_ERR_NONE)
    return grub_errno;

  real_offset = offset;
  while (size)
    {
      char tmp_buf[GRUB_DISK_SECTOR_SIZE];
      grub_size_t len;

      if ((real_offset != 0) || (size < GRUB_DISK_SECTOR_SIZE))
	{
	  len = GRUB_DISK_SECTOR_SIZE - real_offset;
	  if (len > size)
	    len = size;

	  if (buf)
	    {
	      if ((disk->dev->read) (disk, sector, 1, tmp_buf) != GRUB_ERR_NONE)
		break;
	      grub_memcpy (buf, tmp_buf + real_offset, len);
	    }

	  if (disk->read_hook)
	    (disk->read_hook) (sector, real_offset, len, disk->closure);

	  sector++;
	  real_offset = 0;
	}
      else
	{
	  grub_size_t n;

	  len = size & ~(GRUB_DISK_SECTOR_SIZE - 1);
	  n = size >> GRUB_DISK_SECTOR_BITS;

	  if ((buf) &&
	      ((disk->dev->read) (disk, sector, n, buf) != GRUB_ERR_NONE))
	    break;

	  if (disk->read_hook)
	    {
	      while (n)
		{
		  (disk->read_hook) (sector++, 0, GRUB_DISK_SECTOR_SIZE,
				     disk->closure);
		  n--;
		}
	    }
	  else
	    sector += n;
	}

      if (buf)
	buf = (char *) buf + len;
      size -= len;
    }

  return grub_errno;
}