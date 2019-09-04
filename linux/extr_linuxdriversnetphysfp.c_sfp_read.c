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
typedef  int /*<<< orphan*/  u8 ;
struct sfp {int (* read ) (struct sfp*,int,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct sfp*,int,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int sfp_read(struct sfp *sfp, bool a2, u8 addr, void *buf, size_t len)
{
	return sfp->read(sfp, a2, addr, buf, len);
}