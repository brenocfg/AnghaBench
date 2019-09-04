#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m_property {char* priv; } ;
struct TYPE_2__ {double speed_factor_a; double speed_factor_v; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
 int M_PROPERTY_PRINT ; 
 int /*<<< orphan*/  abort () ; 
 int m_property_double_ro (int,void*,double) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,double) ; 

__attribute__((used)) static int mp_property_av_speed_correction(void *ctx, struct m_property *prop,
                                           int action, void *arg)
{
    MPContext *mpctx = ctx;
    char *type = prop->priv;
    double val = 0;
    switch (type[0]) {
    case 'a': val = mpctx->speed_factor_a; break;
    case 'v': val = mpctx->speed_factor_v; break;
    default: abort();
    }

    if (action == M_PROPERTY_PRINT) {
        *(char **)arg = talloc_asprintf(NULL, "%+.05f%%", (val - 1) * 100);
        return M_PROPERTY_OK;
    }

    return m_property_double_ro(action, arg, val);
}