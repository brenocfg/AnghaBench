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
struct cfsrvl {int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int ENOTCONN ; 

bool cfsrvl_ready(struct cfsrvl *service, int *err)
{
	if (!service->open) {
		*err = -ENOTCONN;
		return false;
	}
	return true;
}