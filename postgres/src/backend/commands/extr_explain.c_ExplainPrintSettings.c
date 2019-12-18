#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct config_generic {char* name; } ;
struct TYPE_11__ {scalar_t__ format; int /*<<< orphan*/  settings; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ ExplainState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExplainCloseGroup (char*,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainOpenGroup (char*,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ExplainPropertyText (char*,char*,TYPE_2__*) ; 
 char* GetConfigOptionByName (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 struct config_generic** get_explain_guc_options (int*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static void
ExplainPrintSettings(ExplainState *es)
{
	int			num;
	struct config_generic **gucs;

	/* bail out if information about settings not requested */
	if (!es->settings)
		return;

	/* request an array of relevant settings */
	gucs = get_explain_guc_options(&num);

	/* also bail out of there are no options */
	if (!num)
		return;

	if (es->format != EXPLAIN_FORMAT_TEXT)
	{
		int			i;

		ExplainOpenGroup("Settings", "Settings", true, es);

		for (i = 0; i < num; i++)
		{
			char	   *setting;
			struct config_generic *conf = gucs[i];

			setting = GetConfigOptionByName(conf->name, NULL, true);

			ExplainPropertyText(conf->name, setting, es);
		}

		ExplainCloseGroup("Settings", "Settings", true, es);
	}
	else
	{
		int			i;
		StringInfoData str;

		initStringInfo(&str);

		for (i = 0; i < num; i++)
		{
			char	   *setting;
			struct config_generic *conf = gucs[i];

			if (i > 0)
				appendStringInfoString(&str, ", ");

			setting = GetConfigOptionByName(conf->name, NULL, true);

			if (setting)
				appendStringInfo(&str, "%s = '%s'", conf->name, setting);
			else
				appendStringInfo(&str, "%s = NULL", conf->name);
		}

		if (num > 0)
			ExplainPropertyText("Settings", str.data, es);
	}
}