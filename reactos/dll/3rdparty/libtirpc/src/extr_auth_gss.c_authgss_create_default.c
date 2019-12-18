#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_gss_sec {int dummy; } ;
typedef  scalar_t__ gss_name_t ;
struct TYPE_4__ {char* value; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_5__ {int /*<<< orphan*/  cf_stat; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  CLIENT ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 scalar_t__ GSS_C_NO_NAME ; 
 scalar_t__ GSS_C_NT_HOSTBASED_SERVICE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  RPC_AUTHERROR ; 
 int /*<<< orphan*/ * authgss_create (int /*<<< orphan*/ *,scalar_t__,struct rpc_gss_sec*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ gss_import_name (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 
 TYPE_2__ rpc_createerr ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 

AUTH *
authgss_create_default(CLIENT *clnt, char *service, struct rpc_gss_sec *sec)
{
	AUTH			*auth;
	OM_uint32		 maj_stat = 0, min_stat = 0;
	gss_buffer_desc		 sname;
	gss_name_t		 name = GSS_C_NO_NAME;

	log_debug("in authgss_create_default()");


	sname.value = service;
	sname.length = strlen(service);

	maj_stat = gss_import_name(&min_stat, &sname,
		(gss_OID)GSS_C_NT_HOSTBASED_SERVICE,
		&name);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_import_name", maj_stat, min_stat);
		rpc_createerr.cf_stat = RPC_AUTHERROR;
		return (NULL);
	}

	auth = authgss_create(clnt, name, sec);

	if (name != GSS_C_NO_NAME) {
#ifdef DEBUG
	fprintf(stderr, "authgss_create_default: freeing name %p\n", name);
#endif
 		gss_release_name(&min_stat, &name);
	}

	return (auth);
}