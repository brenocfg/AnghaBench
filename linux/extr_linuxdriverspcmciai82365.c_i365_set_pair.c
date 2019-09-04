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
typedef  int u_short ;

/* Variables and functions */
 int /*<<< orphan*/  i365_set (int,int,int) ; 

__attribute__((used)) static void i365_set_pair(u_short sock, u_short reg, u_short data)
{
    i365_set(sock, reg, data & 0xff);
    i365_set(sock, reg+1, data >> 8);
}