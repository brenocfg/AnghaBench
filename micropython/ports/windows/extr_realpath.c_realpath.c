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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  _MAX_PATH ; 
 char* _fullpath (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 char* to_unix_path (char*) ; 

char *realpath(const char *path, char *resolved_path) {
    char *ret = NULL;
    if (path == NULL) {
        errno = EINVAL;
    } else if (access(path, R_OK) == 0) {
        ret = resolved_path;
        if (ret == NULL)
            ret = malloc(_MAX_PATH);
        if (ret == NULL) {
            errno = ENOMEM;
        } else {
            ret = _fullpath(ret, path, _MAX_PATH);
            if (ret == NULL)
                errno = EIO;
        }
    }
    return to_unix_path(ret);
}