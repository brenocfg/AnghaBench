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
 int /*<<< orphan*/  MY_LDRV_ID ; 
 scalar_t__ TRUE ; 
 size_t c_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ c_strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ is_current_drive ; 
 int /*<<< orphan*/  myspiffs_fs_fns ; 

vfs_fs_fns *myspiffs_realm( const char *inname, char **outname, int set_current_drive ) {
  if (inname[0] == '/') {
    size_t idstr_len = c_strlen( MY_LDRV_ID );
    // logical drive is specified, check if it's our id
    if (0 == c_strncmp( &(inname[1]), MY_LDRV_ID, idstr_len )) {
      *outname = (char *)&(inname[1 + idstr_len]);
      if (*outname[0] == '/') {
        // skip leading /
        (*outname)++;
      }

      if (set_current_drive) is_current_drive = TRUE;
      return &myspiffs_fs_fns;
    }
  } else {
    // no logical drive in patchspec, are we current drive?
    if (is_current_drive) {
      *outname = (char *)inname;
      return &myspiffs_fs_fns;
    }
  }

  if (set_current_drive) is_current_drive = FALSE;
  return NULL;
}