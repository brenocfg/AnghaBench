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
typedef  int /*<<< orphan*/  t ;
struct MPContext {int /*<<< orphan*/  mconfig; } ;
typedef  int /*<<< orphan*/  m_profile_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 char* BSTR_P (TYPE_1__) ; 
 int /*<<< orphan*/  FILE_LOCAL_FLAGS ; 
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*,char*) ; 
 int /*<<< orphan*/ * m_config_get_profile0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_config_set_profile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void mp_auto_load_profile(struct MPContext *mpctx, char *category,
                                 bstr item)
{
    if (!item.len)
        return;

    char t[512];
    snprintf(t, sizeof(t), "%s.%.*s", category, BSTR_P(item));
    m_profile_t *p = m_config_get_profile0(mpctx->mconfig, t);
    if (p) {
        MP_INFO(mpctx, "Auto-loading profile '%s'\n", t);
        m_config_set_profile(mpctx->mconfig, t, FILE_LOCAL_FLAGS);
    }
}