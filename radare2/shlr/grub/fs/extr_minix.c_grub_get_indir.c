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
struct grub_minix_sblock {int dummy; } ;
struct grub_minix_data {int version; int /*<<< orphan*/  disk; struct grub_minix_sblock sblock; } ;
typedef  int /*<<< orphan*/  grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_uint16_t ;

/* Variables and functions */
 int GRUB_MINIX_LOG2_ZONESZ ; 
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int,int,int,char*) ; 
 int grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 int grub_le_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_get_indir (int zone, int num, struct grub_minix_data *data)
{
  struct grub_minix_sblock *sblock = &data->sblock;
  if (data->version == 1)
    {
      grub_uint16_t indir16;
      grub_disk_read (data->disk,
		      zone << GRUB_MINIX_LOG2_ZONESZ,
		      sizeof (grub_uint16_t) * num,
		      sizeof (grub_uint16_t), (char *) &indir16);
      return grub_le_to_cpu16 (indir16);
    }
  else
    {
      grub_uint32_t indir32;
      grub_disk_read (data->disk,
		      zone << GRUB_MINIX_LOG2_ZONESZ,
		      sizeof (grub_uint32_t) * num,
		      sizeof (grub_uint32_t), (char *) &indir32);
      return grub_le_to_cpu32 (indir32);
    }
}