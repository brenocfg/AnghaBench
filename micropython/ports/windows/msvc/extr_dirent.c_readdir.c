#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {int /*<<< orphan*/  d_type; scalar_t__ d_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwFileAttributes; scalar_t__ cFileName; } ;
struct TYPE_4__ {struct dirent result; TYPE_3__ findData; int /*<<< orphan*/  findHandle; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 scalar_t__ FindNextFile (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  errno ; 

struct dirent *readdir(DIR *dir) {
    if (!dir) {
        errno = EBADF;
        return NULL;
    }

    // first pass d_name is NULL so use result from FindFirstFile in opendir, else use FindNextFile
    if (!dir->result.d_name || FindNextFile(dir->findHandle, &dir->findData)) {
        dir->result.d_name = dir->findData.cFileName;
        dir->result.d_type = dir->findData.dwFileAttributes;
        return &dir->result;
    }

    return NULL;
}