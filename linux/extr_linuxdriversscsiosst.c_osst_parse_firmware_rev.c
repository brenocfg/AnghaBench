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

__attribute__((used)) static unsigned int osst_parse_firmware_rev (const char * str)
{
	if (str[1] == '.') {
		return (str[0]-'0')*10000
			+(str[2]-'0')*1000
			+(str[3]-'0')*100;
	} else {
		return (str[0]-'0')*10000
			+(str[1]-'0')*1000
			+(str[2]-'0')*100 - 100
			+(str[3]-'@');
	}
}