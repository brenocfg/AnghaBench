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
struct TYPE_2__ {scalar_t__ pid; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SCORE_IDLE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
score_kill(struct score_board *scb) {
    int i;
    for (i = 0; i < scb->maxproc; i++) {
        if (scb->proc[i].pid != 0 && scb->proc[i].state == SCORE_IDLE) {
            kill(scb->proc[i].pid, SIGTERM);
            return;
        }
    }
}