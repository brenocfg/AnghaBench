#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {char* icon; char* icon_alt; char* type; int size; char* unit; char* name; char const* zebra_class; } ;
struct file_list {TYPE_1__ file_list; int /*<<< orphan*/  full_path; } ;
struct dirent {char* d_name; } ;
struct coro {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ coro_yield (struct coro*,int) ; 
 int dirfd (int /*<<< orphan*/ *) ; 
 scalar_t__ fstatat (int,char*,struct stat*,int /*<<< orphan*/ ) ; 
 char* lwan_determine_mime_type_for_file_name (char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int directory_list_generator(struct coro *coro, void *data)
{
    static const char *zebra_classes[] = {"odd", "even"};
    struct file_list *fl = data;
    struct dirent *entry;
    int zebra_class = 0;
    DIR *dir;
    int fd;

    dir = opendir(fl->full_path);
    if (!dir)
        return 0;

    fd = dirfd(dir);
    if (fd < 0)
        goto out;

    while ((entry = readdir(dir))) {
        struct stat st;

        if (entry->d_name[0] == '.')
            continue;

        if (fstatat(fd, entry->d_name, &st, 0) < 0)
            continue;

        if (S_ISDIR(st.st_mode)) {
            fl->file_list.icon = "folder";
            fl->file_list.icon_alt = "DIR";
            fl->file_list.type = "directory";
        } else if (S_ISREG(st.st_mode)) {
            fl->file_list.icon = "file";
            fl->file_list.icon_alt = "FILE";
            fl->file_list.type =
                lwan_determine_mime_type_for_file_name(entry->d_name);
        } else {
            continue;
        }

        if (st.st_size < 1024) {
            fl->file_list.size = (int)st.st_size;
            fl->file_list.unit = "B";
        } else if (st.st_size < 1024 * 1024) {
            fl->file_list.size = (int)(st.st_size / 1024);
            fl->file_list.unit = "KiB";
        } else if (st.st_size < 1024 * 1024 * 1024) {
            fl->file_list.size = (int)(st.st_size / (1024 * 1024));
            fl->file_list.unit = "MiB";
        } else {
            fl->file_list.size = (int)(st.st_size / (1024 * 1024 * 1024));
            fl->file_list.unit = "GiB";
        }

        fl->file_list.name = entry->d_name;
        fl->file_list.zebra_class = zebra_classes[zebra_class++ % 2];

        if (coro_yield(coro, 1))
            break;
    }

out:
    closedir(dir);
    return 0;
}