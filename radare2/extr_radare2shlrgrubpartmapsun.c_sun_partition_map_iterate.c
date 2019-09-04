#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grub_sun_partition_descriptor {int /*<<< orphan*/  num_sectors; int /*<<< orphan*/  start_cylinder; } ;
struct grub_sun_block {int /*<<< orphan*/  nsect; int /*<<< orphan*/  ntrks; struct grub_sun_partition_descriptor* partitions; TYPE_1__* infos; int /*<<< orphan*/  magic; } ;
struct grub_partition {int dummy; } ;
typedef  int grub_uint64_t ;
typedef  TYPE_2__* grub_partition_t ;
typedef  scalar_t__ grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
struct TYPE_5__ {int start; int number; int index; scalar_t__ len; int /*<<< orphan*/ * partmap; } ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_PART_TABLE ; 
 int GRUB_PARTMAP_SUN_MAGIC ; 
 int GRUB_PARTMAP_SUN_MAX_PARTS ; 
 scalar_t__ GRUB_PARTMAP_SUN_WHOLE_DISK_ID ; 
 int grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct grub_sun_block*) ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (TYPE_2__*) ; 
 int /*<<< orphan*/  grub_sun_is_valid (struct grub_sun_block*) ; 
 int /*<<< orphan*/  grub_sun_partition_map ; 
 scalar_t__ grub_zalloc (int) ; 

__attribute__((used)) static grub_err_t
sun_partition_map_iterate (grub_disk_t disk,
                           int (*hook) (grub_disk_t disk,
					const grub_partition_t partition,
					void *closure),
			   void *closure)
{
  grub_partition_t p;
  struct grub_sun_block block;
  int partnum;
  grub_err_t err;

  p = (grub_partition_t) grub_zalloc (sizeof (struct grub_partition));
  if (! p)
    return grub_errno;

  p->partmap = &grub_sun_partition_map;
  err = grub_disk_read (disk, 0, 0, sizeof (struct grub_sun_block),
			&block);
  if (err)
    {
      grub_free (p);
      return err;
    }

  if (GRUB_PARTMAP_SUN_MAGIC != grub_be_to_cpu16 (block.magic))
    {
      grub_free (p);
      return grub_error (GRUB_ERR_BAD_PART_TABLE, "not a sun partition table");
    }

  if (! grub_sun_is_valid (&block))
    {
      grub_free (p);
      return grub_error (GRUB_ERR_BAD_PART_TABLE, "invalid checksum");
    }

  /* Maybe another error value would be better, because partition
     table _is_ recognized but invalid.  */
  for (partnum = 0; partnum < GRUB_PARTMAP_SUN_MAX_PARTS; partnum++)
    {
      struct grub_sun_partition_descriptor *desc;

      if (block.infos[partnum].id == 0
	  || block.infos[partnum].id == GRUB_PARTMAP_SUN_WHOLE_DISK_ID)
	continue;

      desc = &block.partitions[partnum];
      p->start = ((grub_uint64_t) grub_be_to_cpu32 (desc->start_cylinder)
		  * grub_be_to_cpu16 (block.ntrks)
		  * grub_be_to_cpu16 (block.nsect));
      p->len = grub_be_to_cpu32 (desc->num_sectors);
      p->number = p->index = partnum;
      if (p->len)
	{
	  if (hook (disk, p, closure))
	    partnum = GRUB_PARTMAP_SUN_MAX_PARTS;
	}
    }

  grub_free (p);

  return grub_errno;
}