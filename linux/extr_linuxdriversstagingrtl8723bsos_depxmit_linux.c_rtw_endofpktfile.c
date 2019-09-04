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
struct pkt_file {scalar_t__ pkt_len; } ;
typedef  int sint ;

/* Variables and functions */

sint rtw_endofpktfile(struct pkt_file *pfile)
{
	if (pfile->pkt_len == 0)
		return true;
	return false;
}