#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  board_name ; 
 TYPE_2__ out ; 
 TYPE_1__ rootfs ; 
 scalar_t__ rootfs_size ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version_name ; 

int check_options()
{
    if (!rootfs.name) {
        ERR("No rootfs filename supplied");
        return -2;
    }

    if (!out.name) {
        ERR("No output filename supplied");
        return -3;
    }

    if (!board_name) {
        ERR("No board-name supplied");
        return -4;
    }

    if (!version_name) {
        ERR("No version supplied");
        return -5;
    }

    if (rootfs_size <= 0) {
        ERR("Invalid rootfs size supplied");
        return -6;
    }

    if (strlen(board_name) > 31) {
        ERR("Board name is to long");
        return -7;
    }
    return 0;
}