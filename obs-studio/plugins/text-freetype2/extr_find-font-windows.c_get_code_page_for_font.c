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
typedef  int uint16_t ;

/* Variables and functions */
 int TT_MAC_LANGID_ANY ; 
#define  TT_PLATFORM_APPLE_UNICODE 131 
#define  TT_PLATFORM_ISO 130 
#define  TT_PLATFORM_MACINTOSH 129 
#define  TT_PLATFORM_MICROSOFT 128 
 unsigned int get_mac_code (int,int) ; 
 int iso_code_count ; 
 unsigned int* iso_codes ; 
 int ms_code_count ; 
 unsigned int* ms_codes ; 

__attribute__((used)) static unsigned int get_code_page_for_font(uint16_t platform_id,
					   uint16_t encoding_id,
					   uint16_t language_id)
{
	unsigned int ret;

	switch (platform_id) {
	case TT_PLATFORM_APPLE_UNICODE:
		return 1201;
	case TT_PLATFORM_MACINTOSH:
		ret = get_mac_code(encoding_id, language_id);
		if (!ret)
			ret = get_mac_code(encoding_id, TT_MAC_LANGID_ANY);
		return ret;
	case TT_PLATFORM_ISO:
		if (encoding_id < iso_code_count)
			return iso_codes[encoding_id];
		break;
	case TT_PLATFORM_MICROSOFT:
		if (encoding_id < ms_code_count)
			return ms_codes[encoding_id];
		break;
	}

	return 0;
}