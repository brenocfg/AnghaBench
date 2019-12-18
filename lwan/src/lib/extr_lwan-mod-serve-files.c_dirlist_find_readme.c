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
struct serve_files_priv {int /*<<< orphan*/  auto_index_readme; } ;
struct lwan_strbuf {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 size_t N_ELEMENTS (char const**) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lwan_strbuf_append_str (struct lwan_strbuf*,char*,size_t) ; 
 char const* lwan_strbuf_get_buffer (struct lwan_strbuf*) ; 
 int open (char*,int) ; 
 scalar_t__ read (int,char*,int) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static const char *dirlist_find_readme(struct lwan_strbuf *readme,
                                       struct serve_files_priv *priv,
                                       const char *full_path)
{
    static const char *candidates[] = {"readme", "readme.txt", "read.me",
                                       "README.TXT", "README"};
    int fd = -1;

    if (!priv->auto_index_readme)
        return NULL;

    for (size_t i = 0; i < N_ELEMENTS(candidates); i++) {
        char buffer[PATH_MAX];
        int r;

        r = snprintf(buffer, PATH_MAX, "%s/%s", full_path, candidates[i]);
        if (r < 0 || r >= PATH_MAX)
            continue;

        fd = open(buffer, O_RDONLY | O_CLOEXEC);
        if (fd < 0)
            continue;

        while (true) {
            ssize_t n = read(fd, buffer, sizeof(buffer));

            if (n < 0) {
                if (errno == EINTR)
                    continue;
                goto error;
            }
            if (!n)
                break;

            if (!lwan_strbuf_append_str(readme, buffer, (size_t)n))
                goto error;
        }

        close(fd);
        return lwan_strbuf_get_buffer(readme);
    }

error:
    if (fd >= 0)
        close(fd);
    return NULL;
}