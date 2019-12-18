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
 int /*<<< orphan*/  PQfinish (scalar_t__) ; 
 scalar_t__* conns ; 
 int nconns ; 

__attribute__((used)) static void
disconnect_atexit(void)
{
	int			i;

	for (i = 0; i < nconns; i++)
		if (conns[i])
			PQfinish(conns[i]);
}