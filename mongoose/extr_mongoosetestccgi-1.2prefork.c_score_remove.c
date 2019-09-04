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
struct score_board {int /*<<< orphan*/  numidle; TYPE_1__* proc; int /*<<< orphan*/  numproc; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ pid; } ;

/* Variables and functions */
 scalar_t__ SCORE_IDLE ; 
 int score_find (struct score_board*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
score_remove(struct score_board *scb, pid_t pid) {
    int i = score_find(scb, pid);
    if (i >= 0) {
        scb->proc[i].pid = 0;
        scb->numproc--;
        if (scb->proc[i].state == SCORE_IDLE) {
            scb->numidle--;
        }
    }
}