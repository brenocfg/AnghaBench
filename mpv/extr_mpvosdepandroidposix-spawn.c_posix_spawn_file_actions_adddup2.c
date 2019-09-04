#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t used; TYPE_1__* action; } ;
typedef  TYPE_2__ posix_spawn_file_actions_t ;
struct TYPE_4__ {int filedes; int newfiledes; } ;

/* Variables and functions */
 size_t MAX_FILE_ACTIONS ; 

int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *fa, int fd, int newfd)
{
    if (fa->used >= MAX_FILE_ACTIONS)
        return -1;
    fa->action[fa->used].filedes = fd;
    fa->action[fa->used].newfiledes = newfd;
    fa->used++;
    return 0;
}