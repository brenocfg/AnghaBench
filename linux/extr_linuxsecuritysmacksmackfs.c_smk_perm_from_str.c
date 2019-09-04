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
 int MAY_APPEND ; 
 int MAY_BRINGUP ; 
 int MAY_EXEC ; 
 int MAY_LOCK ; 
 int MAY_READ ; 
 int MAY_TRANSMUTE ; 
 int MAY_WRITE ; 

__attribute__((used)) static int smk_perm_from_str(const char *string)
{
	int perm = 0;
	const char *cp;

	for (cp = string; ; cp++)
		switch (*cp) {
		case '-':
			break;
		case 'r':
		case 'R':
			perm |= MAY_READ;
			break;
		case 'w':
		case 'W':
			perm |= MAY_WRITE;
			break;
		case 'x':
		case 'X':
			perm |= MAY_EXEC;
			break;
		case 'a':
		case 'A':
			perm |= MAY_APPEND;
			break;
		case 't':
		case 'T':
			perm |= MAY_TRANSMUTE;
			break;
		case 'l':
		case 'L':
			perm |= MAY_LOCK;
			break;
		case 'b':
		case 'B':
			perm |= MAY_BRINGUP;
			break;
		default:
			return perm;
		}
}