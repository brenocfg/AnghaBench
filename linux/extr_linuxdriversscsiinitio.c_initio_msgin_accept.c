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
struct initio_host {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSC_MSG_ACCEPT ; 
 scalar_t__ TUL_SCmd ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_msgin_accept(struct initio_host * host)
{
	outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
	return wait_tulip(host);
}