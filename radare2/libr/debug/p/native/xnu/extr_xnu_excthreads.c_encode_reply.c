#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ msgh_id; int /*<<< orphan*/  msgh_local_port; scalar_t__ msgh_size; int /*<<< orphan*/  msgh_remote_port; int /*<<< orphan*/  msgh_bits; } ;
struct TYPE_5__ {int RetCode; int /*<<< orphan*/  NDR; TYPE_2__ Head; } ;
typedef  TYPE_1__ mig_reply_error_t ;
typedef  scalar_t__ mach_msg_size_t ;
typedef  TYPE_2__ mach_msg_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_REMOTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  NDR_record ; 

__attribute__((used)) static void encode_reply(mig_reply_error_t *reply, mach_msg_header_t *hdr, int code) {
	mach_msg_header_t *rh = &reply->Head;
	rh->msgh_bits = MACH_MSGH_BITS (MACH_MSGH_BITS_REMOTE(hdr->msgh_bits), 0);
	rh->msgh_remote_port = hdr->msgh_remote_port;
	rh->msgh_size = (mach_msg_size_t) sizeof (mig_reply_error_t);
	rh->msgh_local_port = MACH_PORT_NULL;
	rh->msgh_id = hdr->msgh_id + 100;
	reply->NDR = NDR_record;
	reply->RetCode = code;
}