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
 scalar_t__ cursor_drawn ; 
 scalar_t__ vbl_cursor_cnt ; 

__attribute__((used)) static inline void cursor_undrawn(void)
{
    vbl_cursor_cnt = 0;
    cursor_drawn = 0;
}