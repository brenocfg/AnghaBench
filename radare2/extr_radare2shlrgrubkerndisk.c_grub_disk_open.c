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
typedef  scalar_t__ grub_uint64_t ;
typedef  int grub_size_t ;
typedef  TYPE_1__* grub_disk_t ;
typedef  TYPE_2__* grub_disk_dev_t ;
struct TYPE_9__ {scalar_t__ (* open ) (char*,TYPE_1__*) ;struct TYPE_9__* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  partition; TYPE_2__* dev; int /*<<< orphan*/  has_partitions; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GRUB_CACHE_TIMEOUT ; 
 scalar_t__ GRUB_ERR_BAD_DEVICE ; 
 scalar_t__ GRUB_ERR_NONE ; 
 scalar_t__ GRUB_ERR_UNKNOWN_DEVICE ; 
 char* find_part_sep (char const*) ; 
 int /*<<< orphan*/  grub_disk_cache_invalidate_all () ; 
 int /*<<< orphan*/  grub_disk_close (TYPE_1__*) ; 
 TYPE_2__* grub_disk_dev_list ; 
 int /*<<< orphan*/  grub_dprintf (char*,char*,char const*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  grub_error_pop () ; 
 int /*<<< orphan*/  grub_error_push () ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 scalar_t__ grub_get_time_ms () ; 
 scalar_t__ grub_last_time ; 
 char* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  grub_partition_probe (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  grub_strdup (char const*) ; 
 scalar_t__ grub_zalloc (int) ; 
 scalar_t__ stub1 (char*,TYPE_1__*) ; 

grub_disk_t
grub_disk_open (const char *name)
{
  const char *p;
  grub_disk_t disk;
  grub_disk_dev_t dev;
  char *raw = (char *) name;
  grub_uint64_t current_time;

  grub_dprintf ("disk", "Opening `%s'...\n", name);

  disk = (grub_disk_t) grub_zalloc (sizeof (*disk));
  if (! disk)
    return 0;

  disk->name = grub_strdup (name);
  if (! disk->name)
    goto fail;

  p = find_part_sep (name);
  if (p)
    {
      grub_size_t len = p - name;

      raw = grub_malloc (len + 1);
      if (! raw)
	goto fail;

      grub_memcpy (raw, name, len);
      raw[len] = '\0';
    }

  for (dev = grub_disk_dev_list; dev; dev = dev->next)
    {
      if ((dev->open) (raw, disk) == GRUB_ERR_NONE)
	break;
      else if (grub_errno == GRUB_ERR_UNKNOWN_DEVICE)
	grub_errno = GRUB_ERR_NONE;
      else
	goto fail;
    }

  if (! dev)
    {
      grub_error (GRUB_ERR_UNKNOWN_DEVICE, "no such disk");
      goto fail;
    }

  if (p && ! disk->has_partitions)
    {
      grub_error (GRUB_ERR_BAD_DEVICE, "no partition on this disk");
      goto fail;
    }

  disk->dev = dev;

  if (p)
    {
      disk->partition = grub_partition_probe (disk, p + 1);
      if (! disk->partition)
	{
	  grub_error (GRUB_ERR_UNKNOWN_DEVICE, "no such partition");
	  goto fail;
	}
    }

  /* The cache will be invalidated about 2 seconds after a device was
     closed.  */
  current_time = grub_get_time_ms ();

  if (current_time > (grub_last_time
		      + GRUB_CACHE_TIMEOUT * 1000))
    grub_disk_cache_invalidate_all ();

  grub_last_time = current_time;

 fail:

  if (raw && raw != name)
    grub_free (raw);

  if (grub_errno != GRUB_ERR_NONE)
    {
      grub_error_push ();
      grub_dprintf ("disk", "Opening `%s' failed.\n", name);
      grub_error_pop ();

      grub_disk_close (disk);
      return 0;
    }

  return disk;
}