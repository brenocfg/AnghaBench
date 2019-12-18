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
struct grub_fb_data {char* fb_list; int ofs; int pri_size; } ;
struct fb_mbr {scalar_t__ fb_magic; int end_magic; int lba; int boot_base; } ;
struct fb_data {int boot_size; int pri_size; scalar_t__ ver_major; scalar_t__ ver_minor; int list_used; } ;
typedef  scalar_t__ grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ FB_AR_MAGIC_LONG ; 
 scalar_t__ FB_MAGIC_LONG ; 
 scalar_t__ FB_VER_MAJOR ; 
 scalar_t__ FB_VER_MINOR ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 scalar_t__ grub_disk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_fb_data*) ; 
 struct grub_fb_data* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (char*,char*,int) ; 

__attribute__((used)) static struct grub_fb_data *
grub_fbfs_mount (grub_disk_t disk)
{
  struct fb_mbr *m;
  struct fb_data *d;
  char buf[512];
  struct grub_fb_data *data;
  int boot_base, boot_size, list_used, pri_size, ofs, i;
  char *fb_list, *p1, *p2;
  grub_uint32_t *grub32;

  if (grub_disk_read (disk, 0, 0, sizeof (buf), buf))
    goto fail;

  m = (struct fb_mbr *) buf;
  d = (struct fb_data *) buf;
  grub32 = (grub_uint32_t *)&buf;
  if (*grub32 == FB_AR_MAGIC_LONG)
    {
      ofs = 0;
      boot_base = 0;
      boot_size = 0;
      pri_size = 0;
    }
  else
    {
      if ((m->fb_magic != FB_MAGIC_LONG) || (m->end_magic != 0xaa55))
	goto fail;

      ofs = m->lba;
      boot_base = m->boot_base;

      if (grub_disk_read (disk, boot_base + 1 - ofs, 0, sizeof (buf), buf))
	goto fail;

      boot_size = d->boot_size;
      pri_size = d->pri_size;
    }

  if ((d->ver_major != FB_VER_MAJOR) || (d->ver_minor != FB_VER_MINOR))
    goto fail;

  list_used = d->list_used;
  data = grub_malloc (sizeof (*data) + (list_used << 9));
  if (! data)
    goto fail;

  fb_list = data->fb_list;
  if (grub_disk_read (disk, boot_base + 1 + boot_size - ofs, 0,
		      (list_used << 9), fb_list))
    {
      grub_free (data);
      goto fail;
    }

  p1 = p2 = fb_list;
  for (i = 0; i < list_used - 1; i++)
    {
      p1 += 510;
      p2 += 512;
      grub_memcpy (p1, p2, 510);
    }

  data->ofs = ofs;
  data->pri_size = pri_size;
  return data;

 fail:
  grub_error (GRUB_ERR_BAD_FS, "not a fb filesystem");
  return 0;
}