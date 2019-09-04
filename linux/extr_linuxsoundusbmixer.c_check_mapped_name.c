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
struct usbmix_name_map {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_mapped_name(const struct usbmix_name_map *p, char *buf, int buflen)
{
	if (!p || !p->name)
		return 0;

	buflen--;
	return strlcpy(buf, p->name, buflen);
}