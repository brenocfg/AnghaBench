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
typedef  int /*<<< orphan*/  text ;
typedef  int (* PFN ) (char*,void**) ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 char* downcase_truncate_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  px_strerror (int) ; 

__attribute__((used)) static void *
find_provider(text *name,
			  PFN provider_lookup,
			  const char *desc, int silent)
{
	void	   *res;
	char	   *buf;
	int			err;

	buf = downcase_truncate_identifier(VARDATA_ANY(name),
									   VARSIZE_ANY_EXHDR(name),
									   false);

	err = provider_lookup(buf, &res);

	if (err && !silent)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("Cannot use \"%s\": %s", buf, px_strerror(err))));

	pfree(buf);

	return err ? NULL : res;
}