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
struct grub_disk_cache {unsigned long dev_id; unsigned long disk_id; int sector; int lock; scalar_t__ data; } ;
typedef  int grub_disk_addr_t ;

/* Variables and functions */
 int GRUB_DISK_CACHE_SIZE ; 
 unsigned int grub_disk_cache_get_index (unsigned long,unsigned long,int) ; 
 struct grub_disk_cache* grub_disk_cache_table ; 
 int /*<<< orphan*/  grub_free (scalar_t__) ; 

__attribute__((used)) static void
grub_disk_cache_invalidate (unsigned long dev_id, unsigned long disk_id,
			    grub_disk_addr_t sector)
{
  unsigned index;
  struct grub_disk_cache *cache;

  sector &= ~(GRUB_DISK_CACHE_SIZE - 1);
  index = grub_disk_cache_get_index (dev_id, disk_id, sector);
  cache = grub_disk_cache_table + index;

  if (cache->dev_id == dev_id && cache->disk_id == disk_id
      && cache->sector == sector && cache->data)
    {
      cache->lock = 1;
      grub_free (cache->data);
      cache->data = 0;
      cache->lock = 0;
    }
}