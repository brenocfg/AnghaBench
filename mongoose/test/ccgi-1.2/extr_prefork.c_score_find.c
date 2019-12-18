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
struct score_board {int maxproc; TYPE_1__* proc; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */

__attribute__((used)) static int
score_find(struct score_board *scb, pid_t pid) {
    int i;
    for (i = 0; i < scb->maxproc; i++) {
        if (scb->proc[i].pid == pid) {
            return i;
        }
    }
    return -1;
}