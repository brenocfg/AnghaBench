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
struct hidp_session {int dummy; } ;
struct hid_device {struct hidp_session* driver_data; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int HIDP_DATA_RTYPE_OUPUT ; 
 int HIDP_TRANS_DATA ; 
 int hidp_send_intr_message (struct hidp_session*,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int hidp_output_report(struct hid_device *hid, __u8 *data, size_t count)
{
	struct hidp_session *session = hid->driver_data;

	return hidp_send_intr_message(session,
				      HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT,
				      data, count);
}