#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_ntfs_attr {char* attr_cur; char* attr_nxt; int flags; char* attr_end; TYPE_2__* mft; } ;
typedef  int /*<<< orphan*/  grub_size_t ;
typedef  scalar_t__ grub_err_t ;
typedef  scalar_t__ grub_disk_addr_t ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int spc; } ;

/* Variables and functions */
 int AF_ALST ; 
 int BLK_SHR ; 
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 char* find_attr (struct grub_ntfs_attr*,unsigned char) ; 
 scalar_t__ grub_divmod64 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_data (struct grub_ntfs_attr*,char*,char*,scalar_t__,int /*<<< orphan*/ ,int,void (*) (scalar_t__,unsigned int,unsigned int,void*),void*,int) ; 
 int u16at (char*,int) ; 
 scalar_t__ u32at (char*,int) ; 

__attribute__((used)) static grub_err_t
read_attr (struct grub_ntfs_attr *at, char *dest, grub_disk_addr_t ofs,
	   grub_size_t len, int cached,
	   void (*read_hook) (grub_disk_addr_t sector,
			      unsigned offset,
			      unsigned length,
			      void *closure),
	   void *closure, int flags)
{
  char *save_cur;
  unsigned char attr;
  char *pp;
  grub_err_t ret;

  save_cur = at->attr_cur;
  at->attr_nxt = at->attr_cur;
  attr = (unsigned char) *at->attr_nxt;
  if (at->flags & AF_ALST)
    {
      char *pa;
      grub_disk_addr_t vcn;

      vcn = grub_divmod64 (ofs, at->mft->data->spc << BLK_SHR, 0);
      pa = at->attr_nxt + u16at (at->attr_nxt, 4);
      while (pa < at->attr_end)
	{
	  if ((unsigned char) *pa != attr)
	    break;
	  if (u32at (pa, 8) > vcn)
	    break;
	  at->attr_nxt = pa;
	  pa += u16at (pa, 4);
	}
    }
  pp = find_attr (at, attr);
  if (pp)
    ret = read_data (at, pp, dest, ofs, len, cached, read_hook, closure, flags);
  else
    ret =
      (grub_errno) ? grub_errno : grub_error (GRUB_ERR_BAD_FS,
					      "attribute not found");
  at->attr_cur = save_cur;
  return ret;
}