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
 int /*<<< orphan*/  free (char*) ; 
 char* s_file_level ; 
 char* strdup (char const*) ; 

void cs_log_set_file_level(const char *file_level) {
  char *fl = s_file_level;
  if (file_level != NULL) {
    s_file_level = strdup(file_level);
  } else {
    s_file_level = NULL;
  }
  free(fl);
}