#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * sst_tab; scalar_t__ sst_ss; scalar_t__ sst_dirlen; scalar_t__ sst_len; } ;
typedef  TYPE_1__ cdf_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 

int
cdf_zero_stream(cdf_stream_t *scn)
{
	scn->sst_len = 0;
	scn->sst_dirlen = 0;
	scn->sst_ss = 0;
	efree(scn->sst_tab);
	scn->sst_tab = NULL;
	return -1;
}