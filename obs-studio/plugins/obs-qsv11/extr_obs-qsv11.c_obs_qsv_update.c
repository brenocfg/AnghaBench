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
struct obs_qsv {int /*<<< orphan*/  params; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_QsvCs ; 
 int qsv_encoder_reconfig (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int update_settings (struct obs_qsv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static bool obs_qsv_update(void *data, obs_data_t *settings)
{
	struct obs_qsv *obsqsv = data;
	bool success = update_settings(obsqsv, settings);
	int ret;

	if (success) {
		EnterCriticalSection(&g_QsvCs);

		ret = qsv_encoder_reconfig(obsqsv->context, &obsqsv->params);
		if (ret != 0)
			warn("Failed to reconfigure: %d", ret);

		LeaveCriticalSection(&g_QsvCs);

		return ret == 0;
	}

	return false;
}