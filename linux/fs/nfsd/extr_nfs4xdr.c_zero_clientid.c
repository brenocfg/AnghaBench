#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cl_boot; scalar_t__ cl_id; } ;
typedef  TYPE_1__ clientid_t ;

/* Variables and functions */

__attribute__((used)) static int zero_clientid(clientid_t *clid)
{
	return (clid->cl_boot == 0) && (clid->cl_id == 0);
}