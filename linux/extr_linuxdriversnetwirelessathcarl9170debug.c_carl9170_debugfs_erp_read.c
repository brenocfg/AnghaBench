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
struct ar9170 {size_t erp_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,size_t,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * erp_modes ; 

__attribute__((used)) static char *carl9170_debugfs_erp_read(struct ar9170 *ar, char *buf,
				       size_t bufsize, ssize_t *ret)
{
	ADD(buf, *ret, bufsize, "ERP Setting: (%d) -> %s\n", ar->erp_mode,
	    erp_modes[ar->erp_mode]);
	return buf;
}