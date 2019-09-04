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
struct grub_minix_data {int filename_size; int ino; } ;
typedef  int /*<<< orphan*/  ino ;
typedef  int /*<<< orphan*/  grub_uint16_t ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FILE_TYPE ; 
 int /*<<< orphan*/  GRUB_ERR_FILE_NOT_FOUND ; 
 scalar_t__ GRUB_ERR_NONE ; 
 int GRUB_MINIX_IFDIR ; 
 int GRUB_MINIX_IFLNK ; 
 int GRUB_MINIX_INODE_MODE (struct grub_minix_data*) ; 
 unsigned int GRUB_MINIX_INODE_SIZE (struct grub_minix_data*) ; 
 scalar_t__ grub_errno ; 
 scalar_t__ grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 int /*<<< orphan*/  grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 
 char* grub_malloc (int) ; 
 int /*<<< orphan*/  grub_minix_lookup_symlink (struct grub_minix_data*,int) ; 
 scalar_t__ grub_minix_read_file (struct grub_minix_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,char*) ; 
 int /*<<< orphan*/  grub_minix_read_inode (struct grub_minix_data*,int /*<<< orphan*/ ) ; 
 char* grub_strchr (char*,char) ; 
 int /*<<< orphan*/  grub_strcmp (char*,char*) ; 
 int /*<<< orphan*/  grub_strcpy (char*,char const*) ; 
 scalar_t__ grub_strlen (char const*) ; 

__attribute__((used)) static grub_err_t
grub_minix_find_file (struct grub_minix_data *data, const char *path)
{
  char * fpath = grub_malloc(grub_strlen (path) + 1);
  char *name = fpath;
  char *next;
  unsigned int pos = 0;
  int dirino;

  grub_strcpy (fpath, path);

  /* Skip the first slash.  */
  if (name[0] == '/')
    {
      name++;
      if (!*name)
      {
        grub_free (fpath);
        return 0;
      }
    }

  /* Extract the actual part from the pathname.  */
  next = grub_strchr (name, '/');
  if (next)
    {
      next[0] = '\0';
      next++;
    }

  do
    {
      grub_uint16_t ino;
      char * filename = grub_malloc(data->filename_size + 1);
      if (grub_strlen (name) == 0)
        {
          grub_free (fpath);
          grub_free (filename);
          return GRUB_ERR_NONE;
        }

      if (grub_minix_read_file (data, 0, 0, pos, sizeof (ino),
				(char *) &ino) < 0)
        {
          grub_free (fpath);
          grub_free (filename);
          return grub_errno;
        }
      if (grub_minix_read_file (data, 0, 0, pos + sizeof (ino),
				data->filename_size, (char *) filename)< 0)
        {
          grub_free (fpath);
          grub_free (filename);
          return grub_errno;
        }

      filename[data->filename_size] = '\0';

      /* Check if the current direntry matches the current part of the
	 pathname.  */
      if (!grub_strcmp (name, filename))
	{
	  dirino = data->ino;
	  grub_minix_read_inode (data, grub_le_to_cpu16 (ino));

	  /* Follow the symlink.  */
	  if ((GRUB_MINIX_INODE_MODE (data)
	       & GRUB_MINIX_IFLNK) == GRUB_MINIX_IFLNK)
	    {
	      grub_minix_lookup_symlink (data, dirino);
	      if (grub_errno)
                {
                  grub_free (fpath);
                  grub_free (filename);
                  return grub_errno;
                }
	    }

	  if (!next)
            {
              grub_free (fpath);
              grub_free (filename);
              return 0;
            }

	  pos = 0;

	  name = next;
	  next = grub_strchr (name, '/');
	  if (next)
	    {
	      next[0] = '\0';
	      next++;
	    }

     	  if ((GRUB_MINIX_INODE_MODE (data)
	       & GRUB_MINIX_IFDIR) != GRUB_MINIX_IFDIR)
            {
              grub_free (fpath);
              grub_free (filename);
              return grub_error (GRUB_ERR_BAD_FILE_TYPE, "not a directory");
            }
          grub_free (filename);
	  continue;
	}

      pos += sizeof (ino) + data->filename_size;
    } while (pos < GRUB_MINIX_INODE_SIZE (data));

  grub_free (fpath);
  grub_error (GRUB_ERR_FILE_NOT_FOUND, "file not found");
  return grub_errno;
}