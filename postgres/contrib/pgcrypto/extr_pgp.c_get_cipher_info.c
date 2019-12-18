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
struct cipher_info {int code; scalar_t__ name; } ;

/* Variables and functions */
 struct cipher_info* cipher_list ; 

__attribute__((used)) static const struct cipher_info *
get_cipher_info(int code)
{
	const struct cipher_info *i;

	for (i = cipher_list; i->name; i++)
		if (i->code == code)
			return i;
	return NULL;
}