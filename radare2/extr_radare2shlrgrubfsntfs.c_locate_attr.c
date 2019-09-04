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
struct grub_ntfs_file {int dummy; } ;
struct grub_ntfs_attr {int flags; } ;

/* Variables and functions */
 int AF_ALST ; 
 int /*<<< orphan*/  GRUB_ERR_NONE ; 
 char* find_attr (struct grub_ntfs_attr*,unsigned char) ; 
 int /*<<< orphan*/  free_attr (struct grub_ntfs_attr*) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  init_attr (struct grub_ntfs_attr*,struct grub_ntfs_file*) ; 

__attribute__((used)) static char *
locate_attr (struct grub_ntfs_attr *at, struct grub_ntfs_file *mft,
	     unsigned char attr)
{
  char *pa;

  init_attr (at, mft);
  if ((pa = find_attr (at, attr)) == NULL)
    return NULL;
  if ((at->flags & AF_ALST) == 0)
    {
      while (1)
	{
	  if ((pa = find_attr (at, attr)) == NULL)
	    break;
	  if (at->flags & AF_ALST)
	    return pa;
	}
      grub_errno = GRUB_ERR_NONE;
      free_attr (at);
      init_attr (at, mft);
      pa = find_attr (at, attr);
    }
  return pa;
}