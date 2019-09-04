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
struct mon_msg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mon_dcss_end ; 
 scalar_t__ mon_dcss_start ; 
 scalar_t__ mon_mca_end (struct mon_msg*) ; 
 int mon_mca_size (struct mon_msg*) ; 
 scalar_t__ mon_mca_start (struct mon_msg*) ; 
 scalar_t__ mon_mca_type (struct mon_msg*,int) ; 
 scalar_t__ mon_rec_end (struct mon_msg*) ; 
 scalar_t__ mon_rec_start (struct mon_msg*) ; 

__attribute__((used)) static int mon_check_mca(struct mon_msg *monmsg)
{
	if ((mon_rec_end(monmsg) <= mon_rec_start(monmsg)) ||
	    (mon_rec_start(monmsg) < mon_dcss_start) ||
	    (mon_rec_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_type(monmsg, 0) == 0) ||
	    (mon_mca_size(monmsg) % 12 != 0) ||
	    (mon_mca_end(monmsg) <= mon_mca_start(monmsg)) ||
	    (mon_mca_end(monmsg) > mon_dcss_end) ||
	    (mon_mca_start(monmsg) < mon_dcss_start) ||
	    ((mon_mca_type(monmsg, 1) == 0) && (mon_mca_type(monmsg, 2) == 0)))
		return -EINVAL;
	return 0;
}