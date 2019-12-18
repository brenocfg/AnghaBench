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
struct machines {int /*<<< orphan*/  guests; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_KERNEL_ID ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  machine__init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void machines__init(struct machines *machines)
{
	machine__init(&machines->host, "", HOST_KERNEL_ID);
	machines->guests = RB_ROOT_CACHED;
}