#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* DYNAMIC_LIBNAME; int no_vcheck; char* engine_id; int list_add_value; int dir_load; int /*<<< orphan*/  dirs; int /*<<< orphan*/ * dynamic_dso; } ;
typedef  TYPE_1__ dynamic_data_ctx ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
#define  DYNAMIC_CMD_DIR_ADD 134 
#define  DYNAMIC_CMD_DIR_LOAD 133 
#define  DYNAMIC_CMD_ID 132 
#define  DYNAMIC_CMD_LIST_ADD 131 
#define  DYNAMIC_CMD_LOAD 130 
#define  DYNAMIC_CMD_NO_VCHECK 129 
#define  DYNAMIC_CMD_SO_PATH 128 
 int /*<<< orphan*/  ENGINE_F_DYNAMIC_CTRL ; 
 int /*<<< orphan*/  ENGINE_R_ALREADY_LOADED ; 
 int /*<<< orphan*/  ENGINE_R_CTRL_COMMAND_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  ENGINE_R_NOT_LOADED ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 void* OPENSSL_strdup (void*) ; 
 TYPE_1__* dynamic_get_data_ctx (int /*<<< orphan*/ *) ; 
 int dynamic_load (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_push (int /*<<< orphan*/ ,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int dynamic_ctrl(ENGINE *e, int cmd, long i, void *p, void (*f) (void))
{
    dynamic_data_ctx *ctx = dynamic_get_data_ctx(e);
    int initialised;

    if (!ctx) {
        ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_NOT_LOADED);
        return 0;
    }
    initialised = ((ctx->dynamic_dso == NULL) ? 0 : 1);
    /* All our control commands require the ENGINE to be uninitialised */
    if (initialised) {
        ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_ALREADY_LOADED);
        return 0;
    }
    switch (cmd) {
    case DYNAMIC_CMD_SO_PATH:
        /* a NULL 'p' or a string of zero-length is the same thing */
        if (p && (strlen((const char *)p) < 1))
            p = NULL;
        OPENSSL_free(ctx->DYNAMIC_LIBNAME);
        if (p)
            ctx->DYNAMIC_LIBNAME = OPENSSL_strdup(p);
        else
            ctx->DYNAMIC_LIBNAME = NULL;
        return (ctx->DYNAMIC_LIBNAME ? 1 : 0);
    case DYNAMIC_CMD_NO_VCHECK:
        ctx->no_vcheck = ((i == 0) ? 0 : 1);
        return 1;
    case DYNAMIC_CMD_ID:
        /* a NULL 'p' or a string of zero-length is the same thing */
        if (p && (strlen((const char *)p) < 1))
            p = NULL;
        OPENSSL_free(ctx->engine_id);
        if (p)
            ctx->engine_id = OPENSSL_strdup(p);
        else
            ctx->engine_id = NULL;
        return (ctx->engine_id ? 1 : 0);
    case DYNAMIC_CMD_LIST_ADD:
        if ((i < 0) || (i > 2)) {
            ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_INVALID_ARGUMENT);
            return 0;
        }
        ctx->list_add_value = (int)i;
        return 1;
    case DYNAMIC_CMD_LOAD:
        return dynamic_load(e, ctx);
    case DYNAMIC_CMD_DIR_LOAD:
        if ((i < 0) || (i > 2)) {
            ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_INVALID_ARGUMENT);
            return 0;
        }
        ctx->dir_load = (int)i;
        return 1;
    case DYNAMIC_CMD_DIR_ADD:
        /* a NULL 'p' or a string of zero-length is the same thing */
        if (!p || (strlen((const char *)p) < 1)) {
            ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_INVALID_ARGUMENT);
            return 0;
        }
        {
            char *tmp_str = OPENSSL_strdup(p);
            if (tmp_str == NULL) {
                ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ERR_R_MALLOC_FAILURE);
                return 0;
            }
            if (!sk_OPENSSL_STRING_push(ctx->dirs, tmp_str)) {
                OPENSSL_free(tmp_str);
                ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ERR_R_MALLOC_FAILURE);
                return 0;
            }
        }
        return 1;
    default:
        break;
    }
    ENGINEerr(ENGINE_F_DYNAMIC_CTRL, ENGINE_R_CTRL_COMMAND_NOT_IMPLEMENTED);
    return 0;
}