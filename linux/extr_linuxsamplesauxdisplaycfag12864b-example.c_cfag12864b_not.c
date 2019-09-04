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
 scalar_t__ cfag12864b_isset (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  cfag12864b_set (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  cfag12864b_unset (unsigned char,unsigned char) ; 

__attribute__((used)) static void cfag12864b_not(unsigned char x, unsigned char y)
{
	if (cfag12864b_isset(x, y))
		cfag12864b_unset(x, y);
	else
		cfag12864b_set(x, y);
}