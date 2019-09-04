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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtc_wkalrm {int /*<<< orphan*/  time; scalar_t__ enabled; } ;
struct opal_msg {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int OPAL_ASYNC_COMPLETION ; 
 int OPAL_SUCCESS ; 
 int opal_async_get_token_interruptible () ; 
 int /*<<< orphan*/  opal_async_release_token (int) ; 
 int opal_async_wait_response (int,struct opal_msg*) ; 
 int opal_get_async_rc (struct opal_msg) ; 
 int opal_tpo_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tm_to_opal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int opal_set_tpo_time(struct device *dev, struct rtc_wkalrm *alarm)
{
	u64 h_m_s_ms = 0;
	struct opal_msg msg;
	u32 y_m_d = 0;
	int token, rc;

	/* if alarm is enabled */
	if (alarm->enabled) {
		tm_to_opal(&alarm->time, &y_m_d, &h_m_s_ms);
		pr_debug("Alarm set to %x %llx\n", y_m_d, h_m_s_ms);

	} else {
		pr_debug("Alarm getting disabled\n");
	}

	token = opal_async_get_token_interruptible();
	if (token < 0) {
		if (token != -ERESTARTSYS)
			pr_err("Failed to get the async token\n");

		return token;
	}

	/* TPO, we care about hour and minute */
	rc = opal_tpo_write(token, y_m_d,
			    (u32)((h_m_s_ms >> 32) & 0xffff0000));
	if (rc != OPAL_ASYNC_COMPLETION) {
		rc = -EIO;
		goto exit;
	}

	rc = opal_async_wait_response(token, &msg);
	if (rc) {
		rc = -EIO;
		goto exit;
	}

	rc = opal_get_async_rc(msg);
	if (rc != OPAL_SUCCESS)
		rc = -EIO;

exit:
	opal_async_release_token(token);
	return rc;
}