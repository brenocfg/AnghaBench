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
struct obs_qsv {int /*<<< orphan*/  packet_data; int /*<<< orphan*/  performance_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_qsv*) ; 
 int /*<<< orphan*/  clear_data (struct obs_qsv*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_end_high_performance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_qsv_destroy(void *data)
{
	struct obs_qsv *obsqsv = (struct obs_qsv *)data;

	if (obsqsv) {
		os_end_high_performance(obsqsv->performance_token);
		clear_data(obsqsv);
		da_free(obsqsv->packet_data);
		bfree(obsqsv);
	}
}