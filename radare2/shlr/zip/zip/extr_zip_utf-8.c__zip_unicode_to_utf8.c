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
typedef  int zip_uint8_t ;
typedef  int zip_uint32_t ;

/* Variables and functions */
 int UTF_8_CONTINUE_MATCH ; 
 int UTF_8_LEN_2_MATCH ; 
 int UTF_8_LEN_3_MATCH ; 
 int UTF_8_LEN_4_MATCH ; 

__attribute__((used)) static zip_uint32_t
_zip_unicode_to_utf8(zip_uint32_t codepoint, zip_uint8_t *buf, int len)
{
    if (codepoint < 0x0080) {
        if (len < 1) {
          return len;
        }
	buf[0] = codepoint & 0xff;
	return 1;
    }
    if (codepoint < 0x0800) {
        if (len < 2) {
          return len;
        }
	buf[0] = UTF_8_LEN_2_MATCH | ((codepoint >> 6) & 0x1f);
	buf[1] = UTF_8_CONTINUE_MATCH | (codepoint & 0x3f);
	return 2;
    }
    if (codepoint < 0x10000) {
        if (len < 3) {
          return len;
        }
	buf[0] = UTF_8_LEN_3_MATCH | ((codepoint >> 12) & 0x0f);
	buf[1] = UTF_8_CONTINUE_MATCH | ((codepoint >> 6) & 0x3f);
	buf[2] = UTF_8_CONTINUE_MATCH | (codepoint & 0x3f);
	return 3;
    }
    if (len < 4) {
      return len;
    }
    buf[0] = UTF_8_LEN_4_MATCH | ((codepoint >> 18) & 0x07);
    buf[1] = UTF_8_CONTINUE_MATCH | ((codepoint >> 12) & 0x3f);
    buf[2] = UTF_8_CONTINUE_MATCH | ((codepoint >> 6) & 0x3f);
    buf[3] = UTF_8_CONTINUE_MATCH | (codepoint & 0x3f);
    return 4;
}