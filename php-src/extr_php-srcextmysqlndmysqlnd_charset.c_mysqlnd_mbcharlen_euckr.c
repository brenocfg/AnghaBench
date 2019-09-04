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
 scalar_t__ valid_euckr (unsigned int const) ; 

__attribute__((used)) static unsigned int mysqlnd_mbcharlen_euckr(const unsigned int kr)
{
	return (valid_euckr(kr)) ? 2 : 1;
}