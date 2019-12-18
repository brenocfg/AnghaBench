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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
#define  LICENCE_TAG_ERROR_ALERT 132 
#define  LICENCE_TAG_NEW_LICENCE 131 
#define  LICENCE_TAG_PLATFORM_CHALLANGE 130 
#define  LICENCE_TAG_REQUEST 129 
#define  LICENCE_TAG_UPGRADE_LICENCE 128 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  licence_process_error_alert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_process_new_license (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_process_platform_challenge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_process_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
licence_process(STREAM s)
{
	uint8 tag;

	in_uint8(s, tag);
	in_uint8s(s, 3);	/* version, length */

#if WITH_DEBUG
	DEBUG(("Received licensing PDU (message type 0x%02x)\n", tag));
#endif

	switch (tag)
	{
		case LICENCE_TAG_REQUEST:
			licence_process_request(s);
			break;

		case LICENCE_TAG_PLATFORM_CHALLANGE:
			licence_process_platform_challenge(s);
			break;

		case LICENCE_TAG_NEW_LICENCE:
		case LICENCE_TAG_UPGRADE_LICENCE:
			/* we can handle new and upgrades of licences the same way. */
			licence_process_new_license(s);
			break;

		case LICENCE_TAG_ERROR_ALERT:
			licence_process_error_alert(s);
			break;

		default:
			unimpl("licence tag 0x%02x\n", tag);
	}
}