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
typedef  int /*<<< orphan*/  vfs_fs_fns ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FF_VOLUMES ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  c_strcpy (char*,int /*<<< orphan*/ ) ; 
 char* c_strdup (char const*) ; 
 size_t c_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ c_strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ is_current_drive ; 
 int /*<<< orphan*/  myfatfs_fs_fns ; 
 int /*<<< orphan*/ * volstr ; 

vfs_fs_fns *myfatfs_realm( const char *inname, char **outname, int set_current_drive )
{
  if (inname[0] == '/') {
    char *oname;

    // logical drive is specified, check if it's one of ours
    for (int i = 0; i < FF_VOLUMES; i++) {
      size_t volstr_len = c_strlen( volstr[i] );
      if (0 == c_strncmp( &(inname[1]), volstr[i], volstr_len )) {
        oname = c_strdup( inname );
        c_strcpy( oname, volstr[i] );
        oname[volstr_len] = ':';
        *outname = oname;

        if (set_current_drive) is_current_drive = TRUE;
        return &myfatfs_fs_fns;
      }
    }
  } else {
    // no logical drive in patchspec, are we current drive?
    if (is_current_drive) {
      *outname = c_strdup( inname );
      return &myfatfs_fs_fns;
    }
  }

  if (set_current_drive) is_current_drive = FALSE;
  return NULL;
}