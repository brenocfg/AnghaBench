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
struct c67x00_td {int status; } ;
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EPIPE ; 
 int ETIMEDOUT ; 
 int TD_STATUSMASK_ERR ; 
 int TD_STATUSMASK_STALL ; 
 int TD_STATUSMASK_TMOUT ; 
 int /*<<< orphan*/  dbg_td (struct c67x00_hcd*,struct c67x00_td*,char*) ; 

__attribute__((used)) static int c67x00_td_to_error(struct c67x00_hcd *c67x00, struct c67x00_td *td)
{
	if (td->status & TD_STATUSMASK_ERR) {
		dbg_td(c67x00, td, "ERROR_FLAG");
		return -EILSEQ;
	}
	if (td->status & TD_STATUSMASK_STALL) {
		/* dbg_td(c67x00, td, "STALL"); */
		return -EPIPE;
	}
	if (td->status & TD_STATUSMASK_TMOUT) {
		dbg_td(c67x00, td, "TIMEOUT");
		return -ETIMEDOUT;
	}

	return 0;
}