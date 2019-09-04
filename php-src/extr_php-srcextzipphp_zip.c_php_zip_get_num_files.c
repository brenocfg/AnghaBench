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
 int zip_get_num_files (struct zip*) ; 

__attribute__((used)) static int php_zip_get_num_files(struct zip *za) /* {{{ */
{
	return zip_get_num_files(za);
}