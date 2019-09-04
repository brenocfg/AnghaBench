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
struct fsg_lun {int ro; int initially_ro; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ fsg_lun_is_open (struct fsg_lun*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

ssize_t fsg_show_ro(struct fsg_lun *curlun, char *buf)
{
	return sprintf(buf, "%d\n", fsg_lun_is_open(curlun)
				  ? curlun->ro
				  : curlun->initially_ro);
}