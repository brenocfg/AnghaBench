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
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
#define  EventTriggerRelationId 133 
#define  ForeignDataWrapperRelationId 132 
#define  ForeignServerRelationId 131 
#define  LanguageRelationId 130 
#define  PublicationRelationId 129 
#define  SubscriptionRelationId 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char* gettext_noop (char*) ; 

__attribute__((used)) static void
report_name_conflict(Oid classId, const char *name)
{
	char	   *msgfmt;

	switch (classId)
	{
		case EventTriggerRelationId:
			msgfmt = gettext_noop("event trigger \"%s\" already exists");
			break;
		case ForeignDataWrapperRelationId:
			msgfmt = gettext_noop("foreign-data wrapper \"%s\" already exists");
			break;
		case ForeignServerRelationId:
			msgfmt = gettext_noop("server \"%s\" already exists");
			break;
		case LanguageRelationId:
			msgfmt = gettext_noop("language \"%s\" already exists");
			break;
		case PublicationRelationId:
			msgfmt = gettext_noop("publication \"%s\" already exists");
			break;
		case SubscriptionRelationId:
			msgfmt = gettext_noop("subscription \"%s\" already exists");
			break;
		default:
			elog(ERROR, "unsupported object class %u", classId);
			break;
	}

	ereport(ERROR,
			(errcode(ERRCODE_DUPLICATE_OBJECT),
			 errmsg(msgfmt, name)));
}