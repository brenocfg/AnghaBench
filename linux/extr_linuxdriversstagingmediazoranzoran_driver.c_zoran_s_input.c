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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int wait_grab_pending (struct zoran*) ; 
 int zoran_set_input (struct zoran*,unsigned int) ; 

__attribute__((used)) static int zoran_s_input(struct file *file, void *__fh, unsigned int input)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;
	int res;

	res = zoran_set_input(zr, input);
	if (res)
		return res;

	/* Make sure the changes come into effect */
	res = wait_grab_pending(zr);
	return res;
}