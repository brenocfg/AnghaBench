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
typedef  int /*<<< orphan*/  u32 ;
struct nbu2ss_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nbu2ss_ep0_int (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_epn_int (struct nbu2ss_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _nbu2ss_ep_int(struct nbu2ss_udc *udc, u32 epnum)
{
	if (epnum == 0)
		_nbu2ss_ep0_int(udc);
	else
		_nbu2ss_epn_int(udc, epnum);
}