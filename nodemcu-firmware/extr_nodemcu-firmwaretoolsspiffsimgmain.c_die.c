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
 char** delete_list ; 
 scalar_t__ delete_on_die ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static void die (const char *what)
{
  if (errno == 0) {
    fprintf(stderr, "%s: fatal error\n", what);
  } else {
    perror (what);
  }
  if (delete_on_die) {
    const char **p = delete_list;
    while (*p) {
      unlink(*p);
      p++;
    }
  }
  exit (1);
}