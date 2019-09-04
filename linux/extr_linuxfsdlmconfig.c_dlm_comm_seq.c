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
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_comm {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int EEXIST ; 
 struct dlm_comm* get_comm (int) ; 
 int /*<<< orphan*/  put_comm (struct dlm_comm*) ; 

int dlm_comm_seq(int nodeid, uint32_t *seq)
{
	struct dlm_comm *cm = get_comm(nodeid);
	if (!cm)
		return -EEXIST;
	*seq = cm->seq;
	put_comm(cm);
	return 0;
}