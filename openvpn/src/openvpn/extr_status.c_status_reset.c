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
struct status_output {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  lseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
status_reset(struct status_output *so)
{
    if (so && so->fd >= 0)
    {
        lseek(so->fd, (off_t)0, SEEK_SET);
    }
}