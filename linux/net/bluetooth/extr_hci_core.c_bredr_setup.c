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
struct hci_request {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_FLT_CLEAR_ALL ; 
 int /*<<< orphan*/  HCI_OP_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  HCI_OP_READ_CLASS_OF_DEV ; 
 int /*<<< orphan*/  HCI_OP_READ_CURRENT_IAC_LAP ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_NAME ; 
 int /*<<< orphan*/  HCI_OP_READ_NUM_SUPPORTED_IAC ; 
 int /*<<< orphan*/  HCI_OP_READ_VOICE_SETTING ; 
 int /*<<< orphan*/  HCI_OP_SET_EVENT_FLT ; 
 int /*<<< orphan*/  HCI_OP_WRITE_CA_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bredr_setup(struct hci_request *req)
{
	__le16 param;
	__u8 flt_type;

	/* Read Buffer Size (ACL mtu, max pkt, etc.) */
	hci_req_add(req, HCI_OP_READ_BUFFER_SIZE, 0, NULL);

	/* Read Class of Device */
	hci_req_add(req, HCI_OP_READ_CLASS_OF_DEV, 0, NULL);

	/* Read Local Name */
	hci_req_add(req, HCI_OP_READ_LOCAL_NAME, 0, NULL);

	/* Read Voice Setting */
	hci_req_add(req, HCI_OP_READ_VOICE_SETTING, 0, NULL);

	/* Read Number of Supported IAC */
	hci_req_add(req, HCI_OP_READ_NUM_SUPPORTED_IAC, 0, NULL);

	/* Read Current IAC LAP */
	hci_req_add(req, HCI_OP_READ_CURRENT_IAC_LAP, 0, NULL);

	/* Clear Event Filters */
	flt_type = HCI_FLT_CLEAR_ALL;
	hci_req_add(req, HCI_OP_SET_EVENT_FLT, 1, &flt_type);

	/* Connection accept timeout ~20 secs */
	param = cpu_to_le16(0x7d00);
	hci_req_add(req, HCI_OP_WRITE_CA_TIMEOUT, 2, &param);
}