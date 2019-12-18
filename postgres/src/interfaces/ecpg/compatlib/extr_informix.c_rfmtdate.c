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
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int ECPG_INFORMIX_DATE_CONVERT ; 
 int ECPG_INFORMIX_OUT_OF_MEMORY ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ PGTYPESdate_fmt_asc (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ errno ; 

int
rfmtdate(date d, const char *fmt, char *str)
{
	errno = 0;
	if (PGTYPESdate_fmt_asc(d, fmt, str) == 0)
		return 0;

	if (errno == ENOMEM)
		return ECPG_INFORMIX_OUT_OF_MEMORY;

	return ECPG_INFORMIX_DATE_CONVERT;
}