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
struct obs_qsv {int /*<<< orphan*/ * extra_data; int /*<<< orphan*/ * context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_QsvCs ; 
 int /*<<< orphan*/  qsv_encoder_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_data(struct obs_qsv *obsqsv)
{
	if (obsqsv->context) {
		EnterCriticalSection(&g_QsvCs);
		qsv_encoder_close(obsqsv->context);
		obsqsv->context = NULL;
		LeaveCriticalSection(&g_QsvCs);

		// bfree(obsqsv->sei);
		bfree(obsqsv->extra_data);

		// obsqsv->sei = NULL;
		obsqsv->extra_data = NULL;
	}
}