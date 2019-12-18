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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FuzzerTestOneInput (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (unsigned char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void testfile(const char *pathname)
{
    struct stat st;
    FILE *f;
    unsigned char *buf;
    size_t s;

    if (stat(pathname, &st) < 0 || !S_ISREG(st.st_mode))
        return;
    printf("# %s\n", pathname);
    fflush(stdout);
    f = fopen(pathname, "rb");
    if (f == NULL)
        return;
    buf = malloc(st.st_size);
    if (buf != NULL) {
        s = fread(buf, 1, st.st_size, f);
        OPENSSL_assert(s == (size_t)st.st_size);
        FuzzerTestOneInput(buf, s);
        free(buf);
    }
    fclose(f);
}