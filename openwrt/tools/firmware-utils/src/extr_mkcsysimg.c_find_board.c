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
struct board_info {int /*<<< orphan*/ * model; } ;

/* Variables and functions */
 struct board_info* boards ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ *) ; 

struct board_info *
find_board(char *model)
{
	struct board_info *ret;
	struct board_info *board;

	ret = NULL;
	for (board = boards; board->model != NULL; board++){
		if (strcasecmp(model, board->model) == 0) {
			ret = board;
			break;
		}
	};

	return ret;
}