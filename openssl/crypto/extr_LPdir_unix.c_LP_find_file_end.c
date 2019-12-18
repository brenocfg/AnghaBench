#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ LP_DIR_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int LP_find_file_end(LP_DIR_CTX **ctx)
{
    if (ctx != NULL && *ctx != NULL) {
        int ret = closedir((*ctx)->dir);

        free(*ctx);
        switch (ret) {
        case 0:
            return 1;
        case -1:
            return 0;
        default:
            break;
        }
    }
    errno = EINVAL;
    return 0;
}