#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_3__ {int flagMode; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int FLAGNUM_MAXSIZE ; 
#define  FM_CHAR 130 
#define  FM_LONG 129 
#define  FM_NUM 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  t_isdigit (char*) ; 
 int /*<<< orphan*/  t_iseq (char*,char) ; 
 int /*<<< orphan*/  t_isspace (char*) ; 

__attribute__((used)) static void
getNextFlagFromString(IspellDict *Conf, char **sflagset, char *sflag)
{
	int32		s;
	char	   *next,
			   *sbuf = *sflagset;
	int			maxstep;
	bool		stop = false;
	bool		met_comma = false;

	maxstep = (Conf->flagMode == FM_LONG) ? 2 : 1;

	while (**sflagset)
	{
		switch (Conf->flagMode)
		{
			case FM_LONG:
			case FM_CHAR:
				COPYCHAR(sflag, *sflagset);
				sflag += pg_mblen(*sflagset);

				/* Go to start of the next flag */
				*sflagset += pg_mblen(*sflagset);

				/* Check if we get all characters of flag */
				maxstep--;
				stop = (maxstep == 0);
				break;
			case FM_NUM:
				s = strtol(*sflagset, &next, 10);
				if (*sflagset == next || errno == ERANGE)
					ereport(ERROR,
							(errcode(ERRCODE_CONFIG_FILE_ERROR),
							 errmsg("invalid affix flag \"%s\"", *sflagset)));
				if (s < 0 || s > FLAGNUM_MAXSIZE)
					ereport(ERROR,
							(errcode(ERRCODE_CONFIG_FILE_ERROR),
							 errmsg("affix flag \"%s\" is out of range",
									*sflagset)));
				sflag += sprintf(sflag, "%0d", s);

				/* Go to start of the next flag */
				*sflagset = next;
				while (**sflagset)
				{
					if (t_isdigit(*sflagset))
					{
						if (!met_comma)
							ereport(ERROR,
									(errcode(ERRCODE_CONFIG_FILE_ERROR),
									 errmsg("invalid affix flag \"%s\"",
											*sflagset)));
						break;
					}
					else if (t_iseq(*sflagset, ','))
					{
						if (met_comma)
							ereport(ERROR,
									(errcode(ERRCODE_CONFIG_FILE_ERROR),
									 errmsg("invalid affix flag \"%s\"",
											*sflagset)));
						met_comma = true;
					}
					else if (!t_isspace(*sflagset))
					{
						ereport(ERROR,
								(errcode(ERRCODE_CONFIG_FILE_ERROR),
								 errmsg("invalid character in affix flag \"%s\"",
										*sflagset)));
					}

					*sflagset += pg_mblen(*sflagset);
				}
				stop = true;
				break;
			default:
				elog(ERROR, "unrecognized type of Conf->flagMode: %d",
					 Conf->flagMode);
		}

		if (stop)
			break;
	}

	if (Conf->flagMode == FM_LONG && maxstep > 0)
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("invalid affix flag \"%s\" with \"long\" flag value",
						sbuf)));

	*sflag = '\0';
}