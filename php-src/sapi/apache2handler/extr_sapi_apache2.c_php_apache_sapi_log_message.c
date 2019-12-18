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
struct TYPE_3__ {int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ php_struct ;

/* Variables and functions */
 int APLOG_ALERT ; 
 int APLOG_CRIT ; 
 int APLOG_DEBUG ; 
 int APLOG_EMERG ; 
 int APLOG_ERR ; 
 int APLOG_INFO ; 
 int /*<<< orphan*/  APLOG_MARK ; 
 int APLOG_NOTICE ; 
 int APLOG_STARTUP ; 
 int APLOG_WARNING ; 
#define  LOG_ALERT 135 
#define  LOG_CRIT 134 
#define  LOG_DEBUG 133 
#define  LOG_EMERG 132 
#define  LOG_ERR 131 
#define  LOG_INFO 130 
#define  LOG_NOTICE 129 
#define  LOG_WARNING 128 
 TYPE_1__* SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_log_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ap_log_rerror (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static void php_apache_sapi_log_message(char *msg, int syslog_type_int)
{
	php_struct *ctx;
	int aplog_type = APLOG_ERR;

	ctx = SG(server_context);

	switch (syslog_type_int) {
#if LOG_EMERG != LOG_CRIT
		case LOG_EMERG:
			aplog_type = APLOG_EMERG;
			break;
#endif
#if LOG_ALERT != LOG_CRIT
		case LOG_ALERT:
			aplog_type = APLOG_ALERT;
			break;
#endif
		case LOG_CRIT:
			aplog_type = APLOG_CRIT;
			break;
		case LOG_ERR:
			aplog_type = APLOG_ERR;
			break;
		case LOG_WARNING:
			aplog_type = APLOG_WARNING;
			break;
		case LOG_NOTICE:
			aplog_type = APLOG_NOTICE;
			break;
#if LOG_INFO != LOG_NOTICE
		case LOG_INFO:
			aplog_type = APLOG_INFO;
			break;
#endif
#if LOG_NOTICE != LOG_DEBUG
		case LOG_DEBUG:
			aplog_type = APLOG_DEBUG;
			break;
#endif
	}

	if (ctx == NULL) { /* we haven't initialized our ctx yet, oh well */
		ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 0, NULL, "%s", msg);
	} else {
		ap_log_rerror(APLOG_MARK, aplog_type, 0, ctx->r, "%s", msg);
	}
}