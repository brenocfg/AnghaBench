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
typedef  int u16 ;
struct p9_req_t {int dummy; } ;
struct p9_client {int max_tag; struct p9_req_t** reqs; } ;

/* Variables and functions */
 int P9_ROW_MAXTAG ; 

struct p9_req_t *p9_tag_lookup(struct p9_client *c, u16 tag)
{
	int row, col;

	/* This looks up the original request by tag so we know which
	 * buffer to read the data into */
	tag++;

	if (tag >= c->max_tag)
		return NULL;

	row = tag / P9_ROW_MAXTAG;
	col = tag % P9_ROW_MAXTAG;

	return &c->reqs[row][col];
}