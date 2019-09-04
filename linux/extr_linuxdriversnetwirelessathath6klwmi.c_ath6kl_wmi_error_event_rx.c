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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_cmd_error_event {int err_code; int /*<<< orphan*/  cmd_id; } ;
struct wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
#define  ILLEGAL_STATE 130 
#define  INTERNAL_ERROR 129 
#define  INVALID_PARAM 128 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int ath6kl_wmi_error_event_rx(struct wmi *wmi, u8 *datap, int len)
{
	const char *type = "unknown error";
	struct wmi_cmd_error_event *ev;
	ev = (struct wmi_cmd_error_event *) datap;

	switch (ev->err_code) {
	case INVALID_PARAM:
		type = "invalid parameter";
		break;
	case ILLEGAL_STATE:
		type = "invalid state";
		break;
	case INTERNAL_ERROR:
		type = "internal error";
		break;
	}

	ath6kl_dbg(ATH6KL_DBG_WMI, "programming error, cmd=%d %s\n",
		   ev->cmd_id, type);

	return 0;
}