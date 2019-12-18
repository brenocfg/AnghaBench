#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int last_error_code; } ;
struct rtmp_stream {int /*<<< orphan*/  output; TYPE_1__ rtmp; } ;

/* Variables and functions */
#define  EACCES 141 
#define  EADDRNOTAVAIL 140 
#define  ECONNABORTED 139 
#define  ECONNRESET 138 
#define  ETIMEDOUT 137 
#define  HOST_NOT_FOUND 136 
#define  NO_DATA 135 
#define  WSAEACCES 134 
#define  WSAEADDRNOTAVAIL 133 
#define  WSAECONNABORTED 132 
#define  WSAECONNRESET 131 
#define  WSAETIMEDOUT 130 
#define  WSAHOST_NOT_FOUND 129 
#define  WSANO_DATA 128 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_output_set_last_error (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void set_output_error(struct rtmp_stream *stream)
{
	const char *msg = NULL;
#ifdef _WIN32
	switch (stream->rtmp.last_error_code) {
	case WSAETIMEDOUT:
		msg = obs_module_text("ConnectionTimedOut");
		break;
	case WSAEACCES:
		msg = obs_module_text("PermissionDenied");
		break;
	case WSAECONNABORTED:
		msg = obs_module_text("ConnectionAborted");
		break;
	case WSAECONNRESET:
		msg = obs_module_text("ConnectionReset");
		break;
	case WSAHOST_NOT_FOUND:
		msg = obs_module_text("HostNotFound");
		break;
	case WSANO_DATA:
		msg = obs_module_text("NoData");
		break;
	case WSAEADDRNOTAVAIL:
		msg = obs_module_text("AddressNotAvailable");
		break;
	}
#else
	switch (stream->rtmp.last_error_code) {
	case ETIMEDOUT:
		msg = obs_module_text("ConnectionTimedOut");
		break;
	case EACCES:
		msg = obs_module_text("PermissionDenied");
		break;
	case ECONNABORTED:
		msg = obs_module_text("ConnectionAborted");
		break;
	case ECONNRESET:
		msg = obs_module_text("ConnectionReset");
		break;
	case HOST_NOT_FOUND:
		msg = obs_module_text("HostNotFound");
		break;
	case NO_DATA:
		msg = obs_module_text("NoData");
		break;
	case EADDRNOTAVAIL:
		msg = obs_module_text("AddressNotAvailable");
		break;
	}
#endif

	// non platform-specific errors
	if (!msg) {
		switch (stream->rtmp.last_error_code) {
		case -0x2700:
			msg = obs_module_text("SSLCertVerifyFailed");
			break;
		}
	}

	obs_output_set_last_error(stream->output, msg);
}