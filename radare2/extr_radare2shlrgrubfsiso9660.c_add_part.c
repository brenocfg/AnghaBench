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
struct grub_iso9660_read_symlink_closure {int /*<<< orphan*/  symlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_realloc (int /*<<< orphan*/ ,int) ; 
 int grub_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_strncat (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
add_part (const char *part, int len,
	  struct grub_iso9660_read_symlink_closure *c)
{
  int size = grub_strlen (c->symlink);

  c->symlink = grub_realloc (c->symlink, size + len + 1);
  if (! c->symlink)
    return;

  grub_strncat (c->symlink, part, len);
}