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
struct csio_lnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_LNE_LINK_DOWN ; 
 int /*<<< orphan*/  csio_post_event_lns (struct csio_lnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_ln_down(struct csio_lnode *ln)
{
	csio_post_event_lns(ln, CSIO_LNE_LINK_DOWN);
}