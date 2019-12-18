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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 char* GetSecurityLabel (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

bool
sepgsql_avc_check_perms(const ObjectAddress *tobject,
						uint16 tclass, uint32 required,
						const char *audit_name,
						bool abort_on_violation)
{
	char	   *tcontext = GetSecurityLabel(tobject, SEPGSQL_LABEL_TAG);
	bool		rc;

	rc = sepgsql_avc_check_perms_label(tcontext,
									   tclass, required,
									   audit_name, abort_on_violation);
	if (tcontext)
		pfree(tcontext);

	return rc;
}