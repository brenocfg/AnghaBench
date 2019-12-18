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
struct dlm_ls {int /*<<< orphan*/  ls_flags; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_NODIR ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dlm_nodir_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	int val;
	int rc = kstrtoint(buf, 0, &val);

	if (rc)
		return rc;
	if (val == 1)
		set_bit(LSFL_NODIR, &ls->ls_flags);
	return len;
}