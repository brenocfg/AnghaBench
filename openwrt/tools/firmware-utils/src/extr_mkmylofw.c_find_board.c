#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cpx_board {int /*<<< orphan*/ * model; } ;

/* Variables and functions */
 struct cpx_board* boards ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ *) ; 

struct cpx_board *
find_board(char *model){
	struct cpx_board *board;
	struct cpx_board *tmp;

	board = NULL;
	for (tmp = boards; tmp->model != NULL; tmp++){
		if (strcasecmp(model, tmp->model) == 0) {
			board = tmp;
			break;
		}
	};

	return board;
}