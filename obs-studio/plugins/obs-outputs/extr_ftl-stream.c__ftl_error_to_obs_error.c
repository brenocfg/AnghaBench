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

/* Variables and functions */
#define  FTL_ALREADY_CONNECTED 156 
#define  FTL_AUDIO_SSRC_COLLISION 155 
#define  FTL_BAD_OR_INVALID_STREAM_KEY 154 
#define  FTL_BAD_REQUEST 153 
#define  FTL_CHANNEL_IN_USE 152 
#define  FTL_CONFIG_ERROR 151 
#define  FTL_CONNECT_ERROR 150 
#define  FTL_DNS_FAILURE 149 
#define  FTL_GAME_BLOCKED 148 
#define  FTL_INTERNAL_ERROR 147 
#define  FTL_MALLOC_FAILURE 146 
#define  FTL_NOT_ACTIVE_STREAM 145 
#define  FTL_NOT_CONNECTED 144 
#define  FTL_NOT_INITIALIZED 143 
#define  FTL_NO_MEDIA_TIMEOUT 142 
#define  FTL_OLD_VERSION 141 
#define  FTL_QUEUE_EMPTY 140 
#define  FTL_QUEUE_FULL 139 
#define  FTL_REGION_UNSUPPORTED 138 
#define  FTL_SOCKET_NOT_CONNECTED 137 
#define  FTL_STATUS_TIMEOUT 136 
#define  FTL_STATUS_WAITING_FOR_KEY_FRAME 135 
#define  FTL_STREAM_REJECTED 134 
#define  FTL_SUCCESS 133 
#define  FTL_UNAUTHORIZED 132 
#define  FTL_UNKNOWN_ERROR_CODE 131 
#define  FTL_UNSUPPORTED_MEDIA_TYPE 130 
#define  FTL_USER_DISCONNECT 129 
#define  FTL_VIDEO_SSRC_COLLISION 128 
 int OBS_OUTPUT_CONNECT_FAILED ; 
 int OBS_OUTPUT_DISCONNECTED ; 
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_SUCCESS ; 

__attribute__((used)) static int _ftl_error_to_obs_error(int status)
{
	/* Map FTL errors to OBS errors */

	switch (status) {
	case FTL_SUCCESS:
		return OBS_OUTPUT_SUCCESS;
	case FTL_SOCKET_NOT_CONNECTED:
	case FTL_MALLOC_FAILURE:
	case FTL_INTERNAL_ERROR:
	case FTL_CONFIG_ERROR:
	case FTL_NOT_ACTIVE_STREAM:
	case FTL_NOT_CONNECTED:
	case FTL_ALREADY_CONNECTED:
	case FTL_STATUS_TIMEOUT:
	case FTL_QUEUE_FULL:
	case FTL_STATUS_WAITING_FOR_KEY_FRAME:
	case FTL_QUEUE_EMPTY:
	case FTL_NOT_INITIALIZED:
		return OBS_OUTPUT_ERROR;
	case FTL_BAD_REQUEST:
	case FTL_DNS_FAILURE:
	case FTL_CONNECT_ERROR:
	case FTL_UNSUPPORTED_MEDIA_TYPE:
	case FTL_OLD_VERSION:
	case FTL_UNAUTHORIZED:
	case FTL_AUDIO_SSRC_COLLISION:
	case FTL_VIDEO_SSRC_COLLISION:
	case FTL_STREAM_REJECTED:
	case FTL_BAD_OR_INVALID_STREAM_KEY:
	case FTL_CHANNEL_IN_USE:
	case FTL_REGION_UNSUPPORTED:
	case FTL_GAME_BLOCKED:
		return OBS_OUTPUT_CONNECT_FAILED;
	case FTL_NO_MEDIA_TIMEOUT:
		return OBS_OUTPUT_DISCONNECTED;
	case FTL_USER_DISCONNECT:
		return OBS_OUTPUT_SUCCESS;
	case FTL_UNKNOWN_ERROR_CODE:
	default:
		/* Unknown FTL error */
		return OBS_OUTPUT_ERROR;
	}
}