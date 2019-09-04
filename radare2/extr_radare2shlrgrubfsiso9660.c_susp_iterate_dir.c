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
struct grub_iso9660_susp_entry {int len; scalar_t__ sig; } ;
struct grub_iso9660_iterate_dir_closure {char** filename; int filename_alloc; int /*<<< orphan*/  type; } ;
typedef  int grub_uint8_t ;
typedef  int grub_uint32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int* ENTRY_DATA (struct grub_iso9660_susp_entry*) ; 
 int /*<<< orphan*/  GRUB_FSHELP_DIR ; 
 int /*<<< orphan*/  GRUB_FSHELP_REG ; 
 int /*<<< orphan*/  GRUB_FSHELP_SYMLINK ; 
 int /*<<< orphan*/  GRUB_FSHELP_UNKNOWN ; 
#define  GRUB_ISO9660_FSTYPE_DIR 130 
 int GRUB_ISO9660_FSTYPE_MASK ; 
#define  GRUB_ISO9660_FSTYPE_REG 129 
#define  GRUB_ISO9660_FSTYPE_SYMLINK 128 
 int GRUB_ISO9660_RR_DOT ; 
 int GRUB_ISO9660_RR_DOTDOT ; 
 int /*<<< orphan*/  grub_realloc (char*,scalar_t__) ; 
 scalar_t__ grub_strlen (char*) ; 
 scalar_t__ grub_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  grub_strncpy (char*,char*,int) ; 
 char* grub_zalloc (int) ; 

__attribute__((used)) static grub_err_t
susp_iterate_dir (struct grub_iso9660_susp_entry *entry, void *closure)
{
  struct grub_iso9660_iterate_dir_closure *c = closure;
  char *filename = *(c->filename);

  /* The filename in the rock ridge entry.  */
  if (grub_strncmp ("NM", (char *) entry->sig, 2) == 0)
    {
      /* The flags are stored at the data position 0, here the
	 filename type is stored.  */
      grub_uint8_t *data = ENTRY_DATA(entry);
      if (data[0] & GRUB_ISO9660_RR_DOT)
	filename = ".";
      else if (data[0] & GRUB_ISO9660_RR_DOTDOT)
	filename = "..";
      else
	{
	  int size = 1;
	  if (filename)
	    {
	      size += grub_strlen (filename);
	      grub_realloc (filename,
			    grub_strlen (filename)
			    + entry->len);
	    }
	  else
	    {
	      size = entry->len - 5;
	      filename = grub_zalloc (size + 1);
	    }
	  c->filename_alloc = 1;
	  grub_strncpy (filename, (char *) data + 1, size);
	  filename[size] = '\0';
	}
    }
  /* The mode information (st_mode).  */
  else if (grub_strncmp ((char *) entry->sig, "PX", 2) == 0)
    {
      /* At position 0 of the PX record the st_mode information is
	 stored (little-endian).  */
      grub_uint8_t *data = ENTRY_DATA(entry);
      grub_uint32_t mode = ((data[0] + (data[1] << 8))
			    & GRUB_ISO9660_FSTYPE_MASK);

      switch (mode)
	{
	case GRUB_ISO9660_FSTYPE_DIR:
	  c->type = GRUB_FSHELP_DIR;
	  break;
	case GRUB_ISO9660_FSTYPE_REG:
	  c->type = GRUB_FSHELP_REG;
	  break;
	case GRUB_ISO9660_FSTYPE_SYMLINK:
	  c->type = GRUB_FSHELP_SYMLINK;
	  break;
	default:
	  c->type = GRUB_FSHELP_UNKNOWN;
	}
    }

  *(c->filename) = filename;
  return 0;
}