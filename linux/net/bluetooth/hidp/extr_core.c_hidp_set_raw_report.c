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
struct hidp_session {int /*<<< orphan*/  report_mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  output_report_success; int /*<<< orphan*/  terminate; int /*<<< orphan*/  report_queue; } ;
struct hid_device {struct hidp_session* driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ERESTARTSYS ; 
 unsigned char HIDP_DATA_RTYPE_FEATURE ; 
 unsigned char HIDP_DATA_RTYPE_INPUT ; 
 unsigned char HIDP_DATA_RTYPE_OUPUT ; 
 unsigned char HIDP_TRANS_SET_REPORT ; 
 int /*<<< orphan*/  HIDP_WAITING_FOR_SEND_ACK ; 
#define  HID_FEATURE_REPORT 130 
#define  HID_INPUT_REPORT 129 
#define  HID_OUTPUT_REPORT 128 
 int HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hidp_send_ctrl_message (struct hidp_session*,unsigned char,unsigned char*,size_t) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hidp_set_raw_report(struct hid_device *hid, unsigned char reportnum,
			       unsigned char *data, size_t count,
			       unsigned char report_type)
{
	struct hidp_session *session = hid->driver_data;
	int ret;

	switch (report_type) {
	case HID_FEATURE_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE;
		break;
	case HID_INPUT_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_INPUT;
		break;
	case HID_OUTPUT_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_OUPUT;
		break;
	default:
		return -EINVAL;
	}

	if (mutex_lock_interruptible(&session->report_mutex))
		return -ERESTARTSYS;

	/* Set up our wait, and send the report request to the device. */
	data[0] = reportnum;
	set_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags);
	ret = hidp_send_ctrl_message(session, report_type, data, count);
	if (ret < 0)
		goto err;

	/* Wait for the ACK from the device. */
	while (test_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags) &&
	       !atomic_read(&session->terminate)) {
		int res;

		res = wait_event_interruptible_timeout(session->report_queue,
			!test_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags)
				|| atomic_read(&session->terminate),
			10*HZ);
		if (res == 0) {
			/* timeout */
			ret = -EIO;
			goto err;
		}
		if (res < 0) {
			/* signal */
			ret = -ERESTARTSYS;
			goto err;
		}
	}

	if (!session->output_report_success) {
		ret = -EIO;
		goto err;
	}

	ret = count;

err:
	clear_bit(HIDP_WAITING_FOR_SEND_ACK, &session->flags);
	mutex_unlock(&session->report_mutex);
	return ret;
}