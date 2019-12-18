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
typedef  int st32 ;

/* Variables and functions */
 int getreg (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static st32 getregmemstart(const char *input) {
	if ((strlen (input) < 1) || (!(*input == '['))) {
		return -1;
	}
	input++;
	return getreg (input);
}