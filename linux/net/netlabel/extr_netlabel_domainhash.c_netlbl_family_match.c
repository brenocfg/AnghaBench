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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 

__attribute__((used)) static bool netlbl_family_match(u16 f1, u16 f2)
{
	return (f1 == f2) || (f1 == AF_UNSPEC) || (f2 == AF_UNSPEC);
}