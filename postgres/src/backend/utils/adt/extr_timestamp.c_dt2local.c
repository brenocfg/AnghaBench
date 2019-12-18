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
typedef  int Timestamp ;

/* Variables and functions */
 int USECS_PER_SEC ; 

__attribute__((used)) static Timestamp
dt2local(Timestamp dt, int tz)
{
	dt -= (tz * USECS_PER_SEC);
	return dt;
}