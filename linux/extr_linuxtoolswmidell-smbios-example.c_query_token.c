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
struct dell_wmi_smbios_buffer {int dummy; } ;
typedef  int __u16 ;

/* Variables and functions */
 int find_token (int,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int token_is_active (int*,int*,struct dell_wmi_smbios_buffer*) ; 

__attribute__((used)) static int query_token(__u16 token, struct dell_wmi_smbios_buffer *buffer)
{
	__u16 location;
	__u16 value;
	int ret;

	ret = find_token(token, &location, &value);
	if (ret != 0) {
		printf("unable to find token %04x\n", token);
		return 1;
	}
	return token_is_active(&location, &value, buffer);
}