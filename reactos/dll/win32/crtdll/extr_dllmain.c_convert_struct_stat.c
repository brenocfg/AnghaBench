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
struct crtdll_stat {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct _stat {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;

/* Variables and functions */

__attribute__((used)) static void convert_struct_stat( struct crtdll_stat *dst, const struct _stat *src )
{
    dst->st_dev   = src->st_dev;
    dst->st_ino   = src->st_ino;
    dst->st_mode  = src->st_mode;
    dst->st_nlink = src->st_nlink;
    dst->st_uid   = src->st_uid;
    dst->st_gid   = src->st_gid;
    dst->st_rdev  = src->st_rdev;
    dst->st_size  = src->st_size;
    dst->st_atime = src->st_atime;
    dst->st_mtime = src->st_mtime;
    dst->st_ctime = src->st_ctime;
}