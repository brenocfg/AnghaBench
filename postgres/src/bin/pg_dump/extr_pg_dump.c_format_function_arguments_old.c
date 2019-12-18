#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * argtypes; TYPE_1__ dobj; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ FuncInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
#define  PROARGMODE_IN 130 
#define  PROARGMODE_INOUT 129 
#define  PROARGMODE_OUT 128 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  atooid (char*) ; 
 char* fmtId (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getFormattedTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_warning (char*) ; 
 int /*<<< orphan*/  zeroAsOpaque ; 

__attribute__((used)) static char *
format_function_arguments_old(Archive *fout,
							  FuncInfo *finfo, int nallargs,
							  char **allargtypes,
							  char **argmodes,
							  char **argnames)
{
	PQExpBufferData fn;
	int			j;

	initPQExpBuffer(&fn);
	appendPQExpBuffer(&fn, "%s(", fmtId(finfo->dobj.name));
	for (j = 0; j < nallargs; j++)
	{
		Oid			typid;
		char	   *typname;
		const char *argmode;
		const char *argname;

		typid = allargtypes ? atooid(allargtypes[j]) : finfo->argtypes[j];
		typname = getFormattedTypeName(fout, typid, zeroAsOpaque);

		if (argmodes)
		{
			switch (argmodes[j][0])
			{
				case PROARGMODE_IN:
					argmode = "";
					break;
				case PROARGMODE_OUT:
					argmode = "OUT ";
					break;
				case PROARGMODE_INOUT:
					argmode = "INOUT ";
					break;
				default:
					pg_log_warning("bogus value in proargmodes array");
					argmode = "";
					break;
			}
		}
		else
			argmode = "";

		argname = argnames ? argnames[j] : (char *) NULL;
		if (argname && argname[0] == '\0')
			argname = NULL;

		appendPQExpBuffer(&fn, "%s%s%s%s%s",
						  (j > 0) ? ", " : "",
						  argmode,
						  argname ? fmtId(argname) : "",
						  argname ? " " : "",
						  typname);
		free(typname);
	}
	appendPQExpBufferChar(&fn, ')');
	return fn.data;
}