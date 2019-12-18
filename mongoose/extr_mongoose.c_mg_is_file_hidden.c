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
struct mg_serve_http_opts {char* per_directory_auth_file; char* hidden_file_pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRSEP ; 
 scalar_t__ mg_match_prefix (char const*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mg_is_file_hidden(const char *path,
                             const struct mg_serve_http_opts *opts,
                             int exclude_specials) {
  const char *p1 = opts->per_directory_auth_file;
  const char *p2 = opts->hidden_file_pattern;

  /* Strip directory path from the file name */
  const char *pdir = strrchr(path, DIRSEP);
  if (pdir != NULL) {
    path = pdir + 1;
  }

  return (exclude_specials && (!strcmp(path, ".") || !strcmp(path, ".."))) ||
         (p1 != NULL && mg_match_prefix(p1, strlen(p1), path) == strlen(p1)) ||
         (p2 != NULL && mg_match_prefix(p2, strlen(p2), path) > 0);
}