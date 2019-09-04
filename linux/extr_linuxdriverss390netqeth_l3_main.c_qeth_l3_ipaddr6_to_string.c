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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void qeth_l3_ipaddr6_to_string(const __u8 *addr, char *buf)
{
	sprintf(buf, "%pI6", addr);
}