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
struct regulatory_request {int processed; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_crda_timeout () ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_requests_list ; 
 int /*<<< orphan*/  reg_requests_lock ; 
 int /*<<< orphan*/  reg_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reg_set_request_processed(void)
{
	bool need_more_processing = false;
	struct regulatory_request *lr = get_last_request();

	lr->processed = true;

	spin_lock(&reg_requests_lock);
	if (!list_empty(&reg_requests_list))
		need_more_processing = true;
	spin_unlock(&reg_requests_lock);

	cancel_crda_timeout();

	if (need_more_processing)
		schedule_work(&reg_work);
}