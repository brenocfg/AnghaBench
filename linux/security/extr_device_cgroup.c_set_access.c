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
 int /*<<< orphan*/  ACCLEN ; 
 short DEVCG_ACC_MKNOD ; 
 short DEVCG_ACC_READ ; 
 short DEVCG_ACC_WRITE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_access(char *acc, short access)
{
	int idx = 0;
	memset(acc, 0, ACCLEN);
	if (access & DEVCG_ACC_READ)
		acc[idx++] = 'r';
	if (access & DEVCG_ACC_WRITE)
		acc[idx++] = 'w';
	if (access & DEVCG_ACC_MKNOD)
		acc[idx++] = 'm';
}