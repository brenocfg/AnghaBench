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
struct grub_hfsplus_catkey_internal {int parent; int /*<<< orphan*/  name; } ;
struct grub_hfsplus_key_internal {struct grub_hfsplus_catkey_internal catkey; } ;
struct grub_hfsplus_catkey {int namelen; int* name; int /*<<< orphan*/  parent; } ;
struct grub_hfsplus_key {struct grub_hfsplus_catkey catkey; } ;
typedef  int /*<<< orphan*/  grub_uint8_t ;

/* Variables and functions */
 int grub_be_to_cpu16 (int) ; 
 int grub_be_to_cpu32 (int /*<<< orphan*/ ) ; 
 int grub_cpu_to_be16 (int) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 char* grub_malloc (int) ; 
 int grub_strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  grub_utf16_to_utf8 (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
grub_hfsplus_cmp_catkey (struct grub_hfsplus_key *keya,
			 struct grub_hfsplus_key_internal *keyb)
{
  struct grub_hfsplus_catkey *catkey_a = &keya->catkey;
  struct grub_hfsplus_catkey_internal *catkey_b = &keyb->catkey;
  char *filename;
  int i;
  int diff;

  diff = grub_be_to_cpu32 (catkey_a->parent) - catkey_b->parent;
  if (diff)
    return diff;

  /* Change the filename in keya so the endianness is correct.  */
  for (i = 0; i < grub_be_to_cpu16 (catkey_a->namelen); i++)
    catkey_a->name[i] = grub_be_to_cpu16 (catkey_a->name[i]);

  filename = grub_malloc (grub_be_to_cpu16 (catkey_a->namelen) + 1);

  if (! grub_utf16_to_utf8 ((grub_uint8_t *) filename, catkey_a->name,
			    grub_be_to_cpu16 (catkey_a->namelen)))
    return -1; /* XXX: This error never occurs, but in case it happens
		  just skip this entry.  */

  diff = grub_strncmp (filename, catkey_b->name,
		       grub_be_to_cpu16 (catkey_a->namelen));

  grub_free (filename);

  /* The endianness was changed to host format, change it back to
     whatever it was.  */
  for (i = 0; i < grub_be_to_cpu16 (catkey_a->namelen); i++)
    catkey_a->name[i] = grub_cpu_to_be16 (catkey_a->name[i]);
  return diff;
}