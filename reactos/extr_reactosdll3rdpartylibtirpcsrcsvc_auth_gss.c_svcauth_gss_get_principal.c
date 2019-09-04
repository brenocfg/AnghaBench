#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t length; int /*<<< orphan*/  value; } ;
struct svc_rpc_gss_data {TYPE_1__ cname; } ;
typedef  int /*<<< orphan*/  SVCAUTH ;

/* Variables and functions */
 struct svc_rpc_gss_data* SVCAUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

char *
svcauth_gss_get_principal(SVCAUTH *auth)
{
	struct svc_rpc_gss_data *gd;
	char *pname;

	gd = SVCAUTH_PRIVATE(auth);

	if (gd->cname.length == 0)
		return (NULL);

	if ((pname = malloc(gd->cname.length + 1)) == NULL)
		return (NULL);

	memcpy(pname, gd->cname.value, gd->cname.length);
	pname[gd->cname.length] = '\0';

	return (pname);
}