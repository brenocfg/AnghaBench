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
struct TYPE_5__ {int /*<<< orphan*/  user_name; TYPE_1__* hba; } ;
struct TYPE_4__ {int auth_method; char* linenumber; char* rawline; } ;
typedef  TYPE_2__ Port ;

/* Variables and functions */
 int ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION ; 
 int ERRCODE_INVALID_PASSWORD ; 
 int /*<<< orphan*/  FATAL ; 
 int STATUS_EOF ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int) ; 
 int /*<<< orphan*/  errdetail_log (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char const*,int /*<<< orphan*/ ) ; 
 char* gettext_noop (char*) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 char* psprintf (char*,char*,char*) ; 
#define  uaBSD 142 
#define  uaCert 141 
#define  uaGSS 140 
#define  uaIdent 139 
#define  uaImplicitReject 138 
#define  uaLDAP 137 
#define  uaMD5 136 
#define  uaPAM 135 
#define  uaPassword 134 
#define  uaPeer 133 
#define  uaRADIUS 132 
#define  uaReject 131 
#define  uaSCRAM 130 
#define  uaSSPI 129 
#define  uaTrust 128 

__attribute__((used)) static void
auth_failed(Port *port, int status, char *logdetail)
{
	const char *errstr;
	char	   *cdetail;
	int			errcode_return = ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION;

	/*
	 * If we failed due to EOF from client, just quit; there's no point in
	 * trying to send a message to the client, and not much point in logging
	 * the failure in the postmaster log.  (Logging the failure might be
	 * desirable, were it not for the fact that libpq closes the connection
	 * unceremoniously if challenged for a password when it hasn't got one to
	 * send.  We'll get a useless log entry for every psql connection under
	 * password auth, even if it's perfectly successful, if we log STATUS_EOF
	 * events.)
	 */
	if (status == STATUS_EOF)
		proc_exit(0);

	switch (port->hba->auth_method)
	{
		case uaReject:
		case uaImplicitReject:
			errstr = gettext_noop("authentication failed for user \"%s\": host rejected");
			break;
		case uaTrust:
			errstr = gettext_noop("\"trust\" authentication failed for user \"%s\"");
			break;
		case uaIdent:
			errstr = gettext_noop("Ident authentication failed for user \"%s\"");
			break;
		case uaPeer:
			errstr = gettext_noop("Peer authentication failed for user \"%s\"");
			break;
		case uaPassword:
		case uaMD5:
		case uaSCRAM:
			errstr = gettext_noop("password authentication failed for user \"%s\"");
			/* We use it to indicate if a .pgpass password failed. */
			errcode_return = ERRCODE_INVALID_PASSWORD;
			break;
		case uaGSS:
			errstr = gettext_noop("GSSAPI authentication failed for user \"%s\"");
			break;
		case uaSSPI:
			errstr = gettext_noop("SSPI authentication failed for user \"%s\"");
			break;
		case uaPAM:
			errstr = gettext_noop("PAM authentication failed for user \"%s\"");
			break;
		case uaBSD:
			errstr = gettext_noop("BSD authentication failed for user \"%s\"");
			break;
		case uaLDAP:
			errstr = gettext_noop("LDAP authentication failed for user \"%s\"");
			break;
		case uaCert:
			errstr = gettext_noop("certificate authentication failed for user \"%s\"");
			break;
		case uaRADIUS:
			errstr = gettext_noop("RADIUS authentication failed for user \"%s\"");
			break;
		default:
			errstr = gettext_noop("authentication failed for user \"%s\": invalid authentication method");
			break;
	}

	cdetail = psprintf(_("Connection matched pg_hba.conf line %d: \"%s\""),
					   port->hba->linenumber, port->hba->rawline);
	if (logdetail)
		logdetail = psprintf("%s\n%s", logdetail, cdetail);
	else
		logdetail = cdetail;

	ereport(FATAL,
			(errcode(errcode_return),
			 errmsg(errstr, port->user_name),
			 logdetail ? errdetail_log("%s", logdetail) : 0));

	/* doesn't return */
}