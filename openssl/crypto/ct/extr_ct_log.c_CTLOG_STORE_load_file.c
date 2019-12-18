#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ invalid_log_entries; int /*<<< orphan*/ * conf; int /*<<< orphan*/ * log_store; } ;
typedef  TYPE_1__ CTLOG_STORE_LOAD_CTX ;
typedef  int /*<<< orphan*/  CTLOG_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_parse_list (char*,char,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CT_F_CTLOG_STORE_LOAD_FILE ; 
 int /*<<< orphan*/  CT_R_LOG_CONF_INVALID ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ NCONF_load (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctlog_store_load_ctx_free (TYPE_1__*) ; 
 TYPE_1__* ctlog_store_load_ctx_new () ; 
 int /*<<< orphan*/  ctlog_store_load_log ; 

int CTLOG_STORE_load_file(CTLOG_STORE *store, const char *file)
{
    int ret = 0;
    char *enabled_logs;
    CTLOG_STORE_LOAD_CTX* load_ctx = ctlog_store_load_ctx_new();

    if (load_ctx == NULL)
        return 0;
    load_ctx->log_store = store;
    load_ctx->conf = NCONF_new(NULL);
    if (load_ctx->conf == NULL)
        goto end;

    if (NCONF_load(load_ctx->conf, file, NULL) <= 0) {
        CTerr(CT_F_CTLOG_STORE_LOAD_FILE, CT_R_LOG_CONF_INVALID);
        goto end;
    }

    enabled_logs = NCONF_get_string(load_ctx->conf, NULL, "enabled_logs");
    if (enabled_logs == NULL) {
        CTerr(CT_F_CTLOG_STORE_LOAD_FILE, CT_R_LOG_CONF_INVALID);
        goto end;
    }

    if (!CONF_parse_list(enabled_logs, ',', 1, ctlog_store_load_log, load_ctx) ||
        load_ctx->invalid_log_entries > 0) {
        CTerr(CT_F_CTLOG_STORE_LOAD_FILE, CT_R_LOG_CONF_INVALID);
        goto end;
    }

    ret = 1;
end:
    NCONF_free(load_ctx->conf);
    ctlog_store_load_ctx_free(load_ctx);
    return ret;
}