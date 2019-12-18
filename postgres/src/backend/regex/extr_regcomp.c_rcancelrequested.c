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

/* Variables and functions */
 scalar_t__ InterruptPending ; 
 scalar_t__ ProcDiePending ; 
 scalar_t__ QueryCancelPending ; 

__attribute__((used)) static int
rcancelrequested(void)
{
	return InterruptPending && (QueryCancelPending || ProcDiePending);
}