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
struct zip {int dummy; } ;

/* Variables and functions */
 scalar_t__ zip_get_archive_comment (struct zip*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * php_zipobj_get_zip_comment(struct zip *za, int *len) /* {{{ */
{
	if (za) {
		return (char *)zip_get_archive_comment(za, len, 0);
	}
	return NULL;
}