#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int header_type; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int type; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ nfs; TYPE_2__ cas; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,char,char*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int ERR_FATAL ; 
#define  HEADER_TYPE_CAS 129 
#define  HEADER_TYPE_NFS 128 
 TYPE_4__* board ; 
 TYPE_4__* find_board (char*) ; 
 TYPE_3__ header ; 
 scalar_t__ required_arg (char,char*) ; 

int
parse_opt_board(char ch, char *arg)
{

	DBG(1,"parsing board option: -%c %s", ch, arg);

	if (board != NULL) {
		ERR("only one board option allowed");
		return ERR_FATAL;
	}

	if (required_arg(ch, arg))
		return ERR_FATAL;

	board = find_board(arg);
	if (board == NULL){
		ERR("invalid/unknown board specified: %s", arg);
		return ERR_FATAL;
	}

	switch (board->header_type) {
	case HEADER_TYPE_CAS:
		header.cas.type = HEADER_TYPE_CAS;
		header.cas.id = board->id;
		break;
	case HEADER_TYPE_NFS:
		header.nfs.type = HEADER_TYPE_NFS;
		header.nfs.id = board->id;
		break;
	default:
		ERR("internal error, unknown header type\n");
		return ERR_FATAL;
	}

	return 0;
}