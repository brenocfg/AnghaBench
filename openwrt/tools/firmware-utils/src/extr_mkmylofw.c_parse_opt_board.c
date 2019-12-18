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
struct TYPE_5__ {int /*<<< orphan*/  flash_size; int /*<<< orphan*/  sdid; int /*<<< orphan*/  svid; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdid; int /*<<< orphan*/  svid; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 TYPE_2__* board ; 
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* find_board (char*) ; 
 int /*<<< orphan*/  flash_size ; 
 TYPE_1__ fw_header ; 
 scalar_t__ required_arg (char,char*) ; 

int
parse_opt_board(char ch, char *arg)
{
	if (required_arg(ch, arg)) {
		goto err_out;
	}

	board = find_board(arg);
	if (board == NULL){
		errmsg(0,"invalid/unknown board specified: %s", arg);
		goto err_out;
	}

	fw_header.vid = board->vid;
	fw_header.did = board->did;
	fw_header.svid = board->svid;
	fw_header.sdid = board->sdid;

	flash_size = board->flash_size;

	return 0;

err_out:
	return -1;
}