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
typedef  int AACENC_ERROR ;

/* Variables and functions */
#define  AACENC_ENCODE_EOF 139 
#define  AACENC_ENCODE_ERROR 138 
#define  AACENC_INIT_AAC_ERROR 137 
#define  AACENC_INIT_ERROR 136 
#define  AACENC_INIT_META_ERROR 135 
#define  AACENC_INIT_SBR_ERROR 134 
#define  AACENC_INIT_TP_ERROR 133 
#define  AACENC_INVALID_CONFIG 132 
#define  AACENC_INVALID_HANDLE 131 
#define  AACENC_MEMORY_ERROR 130 
#define  AACENC_OK 129 
#define  AACENC_UNSUPPORTED_PARAMETER 128 

__attribute__((used)) static const char *libfdk_get_error(AACENC_ERROR err)
{
	switch(err) {
	case AACENC_OK:
		return "No error";
	case AACENC_INVALID_HANDLE:
		return "Invalid handle";
	case AACENC_MEMORY_ERROR:
		return "Memory allocation error";
	case AACENC_UNSUPPORTED_PARAMETER:
		return "Unsupported parameter";
	case AACENC_INVALID_CONFIG:
		return "Invalid config";
	case AACENC_INIT_ERROR:
		return "Initialization error";
	case AACENC_INIT_AAC_ERROR:
		return "AAC library initialization error";
	case AACENC_INIT_SBR_ERROR:
		return "SBR library initialization error";
	case AACENC_INIT_TP_ERROR:
		return "Transport library initialization error";
	case AACENC_INIT_META_ERROR:
		return "Metadata library initialization error";
	case AACENC_ENCODE_ERROR:
		return "Encoding error";
	case AACENC_ENCODE_EOF:
		return "End of file";
	default:
		return "Unknown error";
	}
}