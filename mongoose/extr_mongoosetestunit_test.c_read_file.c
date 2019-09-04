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
struct stat {size_t st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/ * mg_fopen (char const*,char*) ; 

__attribute__((used)) static char *read_file(const char *path, size_t *size) {
  FILE *fp;
  struct stat st;
  char *data = NULL;
  if ((fp = mg_fopen(path, "rb")) != NULL && !fstat(fileno(fp), &st)) {
    *size = st.st_size;
    data = (char *) malloc(*size);
    fread(data, 1, *size, fp);
    fclose(fp);
  }
  return data;
}