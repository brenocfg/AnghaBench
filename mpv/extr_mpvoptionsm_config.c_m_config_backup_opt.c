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
struct m_config_option {int dummy; } ;
struct m_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct m_config*,char*,char const*) ; 
 int /*<<< orphan*/  bstr0 (char const*) ; 
 int /*<<< orphan*/  ensure_backup (struct m_config*,struct m_config_option*) ; 
 struct m_config_option* m_config_get_co (struct m_config*,int /*<<< orphan*/ ) ; 

void m_config_backup_opt(struct m_config *config, const char *opt)
{
    struct m_config_option *co = m_config_get_co(config, bstr0(opt));
    if (co) {
        ensure_backup(config, co);
    } else {
        MP_ERR(config, "Option %s not found.\n", opt);
    }
}