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
struct grub_hfs_record {char* data; struct grub_hfs_catalog_key* key; } ;
struct grub_hfs_dir_closure {int (* hook ) (char*,struct grub_dirhook_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  closure; } ;
struct grub_hfs_catalog_key {int /*<<< orphan*/  strlen; scalar_t__ str; } ;
struct grub_dirhook_info {int dir; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 char GRUB_HFS_FILETYPE_DIR ; 
 char GRUB_HFS_FILETYPE_FILE ; 
 int /*<<< orphan*/  grub_memset (struct grub_dirhook_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  grub_strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (char*,struct grub_dirhook_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
grub_hfs_dir_hook (struct grub_hfs_record *rec, void *closure)
{
  struct grub_hfs_dir_closure *c = closure;
  char fname[32] = { 0 };
  char *filetype = rec->data;
  struct grub_hfs_catalog_key *ckey = rec->key;
  struct grub_dirhook_info info;
  grub_memset (&info, 0, sizeof (info));

  grub_strncpy (fname, (char *) (ckey->str), ckey->strlen);

  if (*filetype == GRUB_HFS_FILETYPE_DIR
      || *filetype == GRUB_HFS_FILETYPE_FILE)
    {
      info.dir = (*filetype == GRUB_HFS_FILETYPE_DIR);
      return c->hook (fname, &info, c->closure);
    }
  return 0;
}