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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ isdotent (char*,int) ; 
 int /*<<< orphan*/  nfserr_badname ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
check_filename(char *str, int len)
{
	int i;

	if (len == 0)
		return nfserr_inval;
	if (isdotent(str, len))
		return nfserr_badname;
	for (i = 0; i < len; i++)
		if (str[i] == '/')
			return nfserr_badname;
	return 0;
}