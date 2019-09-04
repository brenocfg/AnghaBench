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

/* Variables and functions */

__attribute__((used)) static const char *normalize_path( const char *path )
{
#if ! LDRV_TRAVERSAL
  return path;
#else
  const char *temp = path;
  size_t len;

  while ((len = c_strlen( temp )) >= 2) {
    if (temp[0] == '.' && temp[1] == '.') {
      --dir_level;
      if (len >= 4 && dir_level > 0) {
        // prepare next step
        temp = &(temp[4]);
      } else {
        // we're at top, the remainder is expected be an absolute path
        temp = &(temp[3]);
      }
    } else {
      break;
    }
  }

  if (dir_level > 0) {
    // no traversal on root level
    return path;
  } else {
    // path traverses via root
    return temp;
  }
#endif
}