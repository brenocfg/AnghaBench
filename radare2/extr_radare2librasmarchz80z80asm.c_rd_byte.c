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
 char* delspc (char const*) ; 
 char mem_delimiter ; 
 char const* readbyte ; 
 int /*<<< orphan*/  skipword (char const**,char) ; 
 int writebyte ; 

__attribute__((used)) static int rd_byte(const char **p, char delimiter) {
	*p = delspc (*p);
	if (**p == 0) {
		return 0;
	}
	readbyte = *p;
	writebyte = 1;
	mem_delimiter = delimiter;
	skipword (p, delimiter);
	return 1;
}