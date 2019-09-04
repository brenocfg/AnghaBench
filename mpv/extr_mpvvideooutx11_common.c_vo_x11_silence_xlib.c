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
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x11_error_silence ; 

void vo_x11_silence_xlib(int dir)
{
    atomic_fetch_add(&x11_error_silence, dir);
}