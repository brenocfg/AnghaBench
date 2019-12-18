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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ELOOP ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOTDIR ; 
 scalar_t__ LIKELY (int) ; 
 int MAXSYMLINKS ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ fstatat (int,char*,struct stat*,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 char* memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 char* mempmove (char*,char const*,size_t) ; 
 char* rawmemchr (char*,char) ; 
 scalar_t__ readlinkat (int,char*,char*,int) ; 
 scalar_t__ realloc (char*,size_t) ; 
 char* realpath (char const*,char*) ; 
 char* strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

char *
realpathat2(int dirfd, char *dirfdpath, const char *name, char *resolved,
        struct stat *st)
{
    char *rpath, *dest, extra_buf[PATH_MAX];
    const char *start, *end, *rpath_limit;
    int num_links = 0;
    ptrdiff_t dirfdlen;
    char *pathat;

    if (UNLIKELY(name == NULL)) {
        /* As per Single Unix Specification V2 we must return an error if
           either parameter is a null pointer.  We extend this to allow
           the RESOLVED parameter to be NULL in case the we are expected to
           allocate the room for the return value.  */
        errno = EINVAL;
        return NULL;
    }

    /* If any of the additional parameters are null, or if the name to
       resolve the real path is an absolute path, use the standard
       realpath() routine. */
    if (UNLIKELY(dirfd < 0 || dirfdpath == NULL || name[0] == '/'))
        return realpath(name, resolved);

    if (name[0] == '\0') {
        if (UNLIKELY(fstat(dirfd, st) < 0))
            return NULL;
        if (LIKELY(!resolved))
            return strdup(dirfdpath);
        return strcpy(resolved, dirfdpath);
    }

    if (LIKELY(!resolved)) {
        rpath = malloc(PATH_MAX);
        if (UNLIKELY(!rpath))
            return NULL;
    } else
        rpath = resolved;
    rpath_limit = rpath + PATH_MAX;

    strcpy(rpath, dirfdpath);
    dest = rawmemchr(rpath, '\0');
    dirfdlen = dest - rpath;

    for (start = end = name; *start; start = end) {
        int n;

        /* Skip sequence of multiple path-separators.  */
        while (*start == '/')
            ++start;

        /* Find end of path component.  */
        for (end = start; *end && *end != '/'; ++end)
            /* Nothing.  */ ;

        if (end - start == 0)
            break;
        else if (end - start == 1 && start[0] == '.')
            /* nothing */ ;
        else if (end - start == 2 && start[0] == '.' && start[1] == '.') {
            /* Back up to previous component, ignore if at root already.  */
            if (dest > rpath + 1)
                while ((--dest)[-1] != '/');
        } else {
            size_t new_size;

            if (dest[-1] != '/')
                *dest++ = '/';

            if (dest + (end - start) >= rpath_limit) {
                ptrdiff_t dest_offset = dest - rpath;
                char *new_rpath;

                if (UNLIKELY(resolved != NULL)) {
                    errno = ENAMETOOLONG;
                    if (dest > rpath + 1)
                        dest--;
                    *dest = '\0';
                    goto error;
                }

                new_size = (size_t)(rpath_limit - rpath);
                if (end - start + 1 > PATH_MAX)
                    new_size += (size_t)(end - start + 1);
                else
                    new_size += PATH_MAX;
                new_rpath = (char *) realloc(rpath, new_size);
                if (UNLIKELY(new_rpath == NULL))
                    goto error;
                rpath = new_rpath;
                rpath_limit = rpath + new_size;

                dest = rpath + dest_offset;
            }

            dest = mempmove(dest, start, (size_t)(end - start));
            *dest = '\0';

            if ((dirfdlen == 1 && *dirfdpath == '/') ||
                    strncmp(rpath, dirfdpath, (size_t)dirfdlen)) {
                pathat = rpath;
            } else {
                pathat = rpath + dirfdlen + 1;
            }
            if (UNLIKELY(*pathat == '\0'))
                pathat = rpath;

            if (UNLIKELY(fstatat(dirfd, pathat, st, AT_SYMLINK_NOFOLLOW) < 0))
                goto error;

            if (UNLIKELY(S_ISLNK(st->st_mode))) {
                char buf[PATH_MAX];
                size_t len;

                if (UNLIKELY(++num_links > MAXSYMLINKS)) {
                    errno = ELOOP;
                    goto error;
                }

                n = (int)readlinkat(dirfd, pathat, buf, PATH_MAX - 1);
                if (UNLIKELY(n < 0))
                    goto error;
                buf[n] = '\0';

                len = strlen(end);
                if (UNLIKELY((size_t)(PATH_MAX - n) <= len)) {
                    errno = ENAMETOOLONG;
                    goto error;
                }

                /* Careful here, end may be a pointer into extra_buf... */
                memmove(&extra_buf[n], end, len + 1);
                end = memcpy(extra_buf, buf, (size_t)n);

                if (buf[0] == '/')
                    dest = rpath + 1;    /* It's an absolute symlink */
                else
                    /* Back up to previous component, ignore if at root already: */
                    if (dest > rpath + 1)
                        while ((--dest)[-1] != '/');
            } else if (UNLIKELY(!S_ISDIR(st->st_mode) && *end != '\0')) {
                errno = ENOTDIR;
                goto error;
            }
        }
    }

    if (dest > rpath + 1 && dest[-1] == '/')
        --dest;
    *dest = '\0';

    assert(resolved == NULL || resolved == rpath);
    return rpath;

  error:
    assert(resolved == NULL || resolved == rpath);
    if (resolved == NULL)
        free(rpath);
    return NULL;
}