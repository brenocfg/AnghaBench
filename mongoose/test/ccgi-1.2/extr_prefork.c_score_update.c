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
struct score_state {scalar_t__ state; int /*<<< orphan*/  pid; } ;
struct score_board {int /*<<< orphan*/  numidle; TYPE_1__* proc; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SCORE_IDLE ; 
 int score_find (struct score_board*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
score_update(struct score_board *scb, struct score_state *st) {
    int i = score_find(scb, st->pid);
    if (i >= 0 && scb->proc[i].state != st->state) {
        scb->proc[i].state = st->state;
        if (st->state == SCORE_IDLE) {
            scb->numidle++;
        }
        else {
            scb->numidle--;
        }
    }
}