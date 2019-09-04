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
 int NFS4_OK ; 
 int /*<<< orphan*/  dprintf (int,char*,int) ; 

int compound_error(int status)
{
    if (status != NFS4_OK)
        dprintf(1, "COMPOUND failed with status %d.\n", status);
    return status;
}