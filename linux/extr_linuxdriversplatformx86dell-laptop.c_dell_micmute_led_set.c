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
struct calling_interface_token {int /*<<< orphan*/  value; int /*<<< orphan*/  location; } ;
struct calling_interface_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_TOKEN_WRITE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GLOBAL_MIC_MUTE_DISABLE ; 
 int /*<<< orphan*/  GLOBAL_MIC_MUTE_ENABLE ; 
 int /*<<< orphan*/  SELECT_TOKEN_STD ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct calling_interface_token* dell_smbios_find_token (int /*<<< orphan*/ ) ; 

int dell_micmute_led_set(int state)
{
	struct calling_interface_buffer buffer;
	struct calling_interface_token *token;

	if (state == 0)
		token = dell_smbios_find_token(GLOBAL_MIC_MUTE_DISABLE);
	else if (state == 1)
		token = dell_smbios_find_token(GLOBAL_MIC_MUTE_ENABLE);
	else
		return -EINVAL;

	if (!token)
		return -ENODEV;

	dell_fill_request(&buffer, token->location, token->value, 0, 0);
	dell_send_request(&buffer, CLASS_TOKEN_WRITE, SELECT_TOKEN_STD);

	return state;
}