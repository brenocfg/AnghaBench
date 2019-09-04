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
 int /*<<< orphan*/  print (char const*) ; 
 int print_num (unsigned long) ; 

__attribute__((used)) static int print_k_value(const char *s, unsigned long num, unsigned long units)
{
	unsigned long long temp;
	int ccode;

	print(s);

	temp = num;
	temp = (temp * units)/1024;
	num = temp;
	ccode = print_num(num);
	print("\n");
	return ccode;
}