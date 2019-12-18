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
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,unsigned long) ; 

void
buf_size_error(const size_t size)
{
    msg(M_FATAL, "fatal buffer size error, size=%lu", (unsigned long)size);
}