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
typedef  int /*<<< orphan*/  conf_init_func ;
typedef  int /*<<< orphan*/  conf_finish_func ;
typedef  int /*<<< orphan*/  DSO ;
typedef  int /*<<< orphan*/  CONF_MODULE ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_F_MODULE_LOAD_DSO ; 
 int CONF_R_ERROR_LOADING_DSO ; 
 int CONF_R_MISSING_INIT_FUNCTION ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DSO_bind_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSO_load (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_mod_finish_name ; 
 int /*<<< orphan*/  DSO_mod_init_name ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 char* NCONF_get_string (int /*<<< orphan*/  const*,char const*,char*) ; 
 int /*<<< orphan*/ * module_add (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CONF_MODULE *module_load_dso(const CONF *cnf,
                                    const char *name, const char *value)
{
    DSO *dso = NULL;
    conf_init_func *ifunc;
    conf_finish_func *ffunc;
    const char *path = NULL;
    int errcode = 0;
    CONF_MODULE *md;
    /* Look for alternative path in module section */
    path = NCONF_get_string(cnf, value, "path");
    if (!path) {
        ERR_clear_error();
        path = name;
    }
    dso = DSO_load(NULL, path, NULL, 0);
    if (!dso) {
        errcode = CONF_R_ERROR_LOADING_DSO;
        goto err;
    }
    ifunc = (conf_init_func *)DSO_bind_func(dso, DSO_mod_init_name);
    if (!ifunc) {
        errcode = CONF_R_MISSING_INIT_FUNCTION;
        goto err;
    }
    ffunc = (conf_finish_func *)DSO_bind_func(dso, DSO_mod_finish_name);
    /* All OK, add module */
    md = module_add(dso, name, ifunc, ffunc);

    if (!md)
        goto err;

    return md;

 err:
    DSO_free(dso);
    CONFerr(CONF_F_MODULE_LOAD_DSO, errcode);
    ERR_add_error_data(4, "module=", name, ", path=", path);
    return NULL;
}