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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  lwan_status_warning (char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static const char *is_dir(const char *v)
{
    struct stat st;

    if (!v)
        return NULL;

    if (*v != '/')
        return NULL;

    if (stat(v, &st) < 0)
        return NULL;

    if (!S_ISDIR(st.st_mode))
        return NULL;

    if (!(st.st_mode & S_ISVTX)) {
        lwan_status_warning(
            "Using %s as temporary directory, but it doesn't have "
            "the sticky bit set.",
            v);
    }

    return v;
}