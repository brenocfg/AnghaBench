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
struct connection {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  lowcomms_connect_sock (struct connection*) ; 
 struct connection* nodeid2con (int,int /*<<< orphan*/ ) ; 

int dlm_lowcomms_connect_node(int nodeid)
{
	struct connection *con;

	if (nodeid == dlm_our_nodeid())
		return 0;

	con = nodeid2con(nodeid, GFP_NOFS);
	if (!con)
		return -ENOMEM;
	lowcomms_connect_sock(con);
	return 0;
}