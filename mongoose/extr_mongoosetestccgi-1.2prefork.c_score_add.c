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
struct score_board {int /*<<< orphan*/  numidle; int /*<<< orphan*/  numproc; TYPE_1__* proc; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCORE_IDLE ; 
 int score_find (struct score_board*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
score_add(struct score_board *scb, pid_t pid) {
    int i = score_find(scb, 0);
    if (i >= 0) {
        scb->proc[i].pid = pid;
        scb->proc[i].state = SCORE_IDLE;
        scb->numproc++;
        scb->numidle++;
    }
}