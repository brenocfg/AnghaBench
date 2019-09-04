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
struct calling_interface_token {int tokenID; } ;

/* Variables and functions */
 int da_num_tokens ; 
 struct calling_interface_token* da_tokens ; 

struct calling_interface_token *dell_smbios_find_token(int tokenid)
{
	int i;

	if (!da_tokens)
		return NULL;

	for (i = 0; i < da_num_tokens; i++) {
		if (da_tokens[i].tokenID == tokenid)
			return &da_tokens[i];
	}

	return NULL;
}