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
typedef  int zip_uint32_t ;

/* Variables and functions */

__attribute__((used)) static zip_uint32_t
_zip_unicode_to_utf8_len(zip_uint32_t codepoint)
{
    if (codepoint < 0x0080)
	return 1;
    if (codepoint < 0x0800)
	return 2;
    if (codepoint < 0x10000)
	return 3;
    return 4;
}