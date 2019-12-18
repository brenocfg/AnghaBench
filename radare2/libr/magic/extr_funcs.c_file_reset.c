#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {int error; int /*<<< orphan*/  mlist; scalar_t__ haderr; TYPE_1__ o; } ;
typedef  TYPE_2__ RMagic ;

/* Variables and functions */
 int /*<<< orphan*/  file_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int file_reset(RMagic *ms) {
	if (!ms) {
		return 0;
	}
	free (ms->o.buf);
	ms->o.buf = NULL;
	ms->haderr = 0;
	ms->error = -1;
	if (!ms->mlist) {
		file_error (ms, 0, "no magic files loaded! ");
		return -1;
	}
	return 0;
}