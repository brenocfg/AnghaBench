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
typedef  int /*<<< orphan*/  rcode ;
typedef  int /*<<< orphan*/  CONF_MODULE ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  CONF_F_MODULE_RUN ; 
 unsigned long CONF_MFLAGS_NO_DSO ; 
 unsigned long CONF_MFLAGS_SILENT ; 
 int /*<<< orphan*/  CONF_R_MODULE_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  CONF_R_UNKNOWN_MODULE_NAME ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECIMAL_SIZE (int) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*,...) ; 
 int /*<<< orphan*/ * module_find (char const*) ; 
 int module_init (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * module_load_dso (int /*<<< orphan*/  const*,char const*,char const*) ; 

__attribute__((used)) static int module_run(const CONF *cnf, const char *name, const char *value,
                      unsigned long flags)
{
    CONF_MODULE *md;
    int ret;

    md = module_find(name);

    /* Module not found: try to load DSO */
    if (!md && !(flags & CONF_MFLAGS_NO_DSO))
        md = module_load_dso(cnf, name, value);

    if (!md) {
        if (!(flags & CONF_MFLAGS_SILENT)) {
            CONFerr(CONF_F_MODULE_RUN, CONF_R_UNKNOWN_MODULE_NAME);
            ERR_add_error_data(2, "module=", name);
        }
        return -1;
    }

    ret = module_init(md, name, value, cnf);

    if (ret <= 0) {
        if (!(flags & CONF_MFLAGS_SILENT)) {
            char rcode[DECIMAL_SIZE(ret) + 1];

            CONFerr(CONF_F_MODULE_RUN, CONF_R_MODULE_INITIALIZATION_ERROR);
            BIO_snprintf(rcode, sizeof(rcode), "%-8d", ret);
            ERR_add_error_data(6, "module=", name, ", value=", value,
                               ", retcode=", rcode);
        }
    }

    return ret;
}