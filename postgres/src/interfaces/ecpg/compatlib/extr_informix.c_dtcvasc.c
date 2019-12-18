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
typedef  int /*<<< orphan*/  timestamp ;

/* Variables and functions */
 int ECPG_INFORMIX_EXTRA_CHARS ; 
 int /*<<< orphan*/  PGTYPEStimestamp_from_asc (char*,char**) ; 
 int errno ; 

int
dtcvasc(char *str, timestamp * ts)
{
	timestamp	ts_tmp;
	int			i;
	char	  **endptr = &str;

	errno = 0;
	ts_tmp = PGTYPEStimestamp_from_asc(str, endptr);
	i = errno;
	if (i)
		/* TODO: rewrite to Informix error codes */
		return i;
	if (**endptr)
	{
		/* extra characters exist at the end */
		return ECPG_INFORMIX_EXTRA_CHARS;
	}
	/* TODO: other Informix error codes missing */

	/* everything went fine */
	*ts = ts_tmp;

	return 0;
}