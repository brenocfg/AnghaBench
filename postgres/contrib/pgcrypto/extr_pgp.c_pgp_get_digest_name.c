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
struct digest_info {char const* name; int code; } ;

/* Variables and functions */
 struct digest_info* digest_list ; 

const char *
pgp_get_digest_name(int code)
{
	const struct digest_info *i;

	for (i = digest_list; i->name; i++)
		if (i->code == code)
			return i->name;
	return NULL;
}