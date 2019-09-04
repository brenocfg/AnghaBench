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
struct m_property {int dummy; } ;
struct MPOpts {char* record_file; } ;
struct MPContext {struct MPOpts* opts; } ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
 int M_PROPERTY_OK ; 
 int M_PROPERTY_SET ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_property_generic_option (struct MPContext*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  open_recorder (struct MPContext*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mp_property_record_file(void *ctx, struct m_property *prop,
                                   int action, void *arg)
{
    struct MPContext *mpctx = ctx;
    struct MPOpts *opts = mpctx->opts;
    if (action == M_PROPERTY_SET) {
        char *new = *(char **)arg;
        if (!bstr_equals(bstr0(new), bstr0(opts->record_file))) {
            talloc_free(opts->record_file);
            opts->record_file = talloc_strdup(NULL, new);
            open_recorder(mpctx, false);
            // open_recorder() unsets it on failure.
            if (new && !opts->record_file)
                return M_PROPERTY_ERROR;
        }
        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}