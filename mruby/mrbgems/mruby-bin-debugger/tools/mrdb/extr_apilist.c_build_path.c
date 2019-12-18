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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char*
build_path(mrb_state *mrb, const char *dir, const char *base)
{
  int len;
  char *path = NULL;

  len = strlen(base) + 1;

  if (strcmp(dir, ".")) {
    len += strlen(dir) + sizeof("/") - 1;
  }

  path = (char*)mrb_malloc(mrb, len);
  memset(path, 0, len);

  if (strcmp(dir, ".")) {
    strcat(path, dir);
    strcat(path, "/");
  }
  strcat(path, base);

  return path;
}