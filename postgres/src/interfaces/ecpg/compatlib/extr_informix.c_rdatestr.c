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
 char* PGTYPESdate_to_asc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
rdatestr(date d, char *str)
{
	char	   *tmp = PGTYPESdate_to_asc(d);

	if (!tmp)
		return ECPG_INFORMIX_DATE_CONVERT;

	/* move to user allocated buffer */
	strcpy(str, tmp);
	free(tmp);

	return 0;
}