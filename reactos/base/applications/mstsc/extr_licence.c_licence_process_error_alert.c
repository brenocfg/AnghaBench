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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 void* True ; 
 void* g_licence_error_result ; 
 void* g_licence_issued ; 
 int /*<<< orphan*/  in_uint32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

void
licence_process_error_alert(STREAM s)
{
	uint32 error_code;
	uint32 state_transition;
	uint32 error_info;
	in_uint32(s, error_code);
	in_uint32(s, state_transition);
	in_uint32(s, error_info);

	/* There is a special case in the error alert handling, when licensing is all good
	   and the server is not sending a license to client, a "Server License Error PDU -
	   Valid Client" packet is sent which means, every thing is ok.

	   Therefor we should flag that everything is ok with license here.
	 */
	if (error_code == 0x07)
	{
		g_licence_issued = True;
		return;
	}

	/* handle error codes, for now, just report them */
	switch (error_code)
	{
		case 0x6:	// ERR_NO_LICENSE_SERVER
			warning("License error alert from server: No license server\n");
			break;

		case 0x8:	// ERR_INVALID_CLIENT
			warning("License error alert from server: Invalid client\n");
			break;

		case 0x4:	// ERR_INVALID_SCOPE
		case 0xb:	// ERR_INVALID_PRODUCTID
		case 0xc:	// ERR_INVALID_MESSAGE_LENGTH
		default:
			warning("License error alert from server: code %u, state transition %u\n",
				error_code, state_transition);
			break;
	}

	/* handle error codes, for now, just report them */
	switch (error_info)
	{
		default:
			break;
	}

	g_licence_error_result = True;
}