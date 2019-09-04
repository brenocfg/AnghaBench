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
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

sint rtw_endofpktfile(struct pkt_file *pfile)
{
_func_enter_;

	if (pfile->pkt_len == 0) {
_func_exit_;
		return _TRUE;
	}

_func_exit_;

	return _FALSE;
}