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
struct vo {int monitor_par; int /*<<< orphan*/  global; struct priv* priv; TYPE_1__* opts; } ;
struct priv {int /*<<< orphan*/  sws; int /*<<< orphan*/  opts; } ;
struct TYPE_2__ {int monitor_pixel_aspect; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_get_config_group (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sws_alloc (struct vo*) ; 
 int /*<<< orphan*/  vo_tct_conf ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    // most terminal characters aren't 1:1, so we default to 2:1.
    // if user passes their own value of choice, it'll be scaled accordingly.
    vo->monitor_par = vo->opts->monitor_pixel_aspect * 2;

    struct priv *p = vo->priv;
    p->opts = mp_get_config_group(vo, vo->global, &vo_tct_conf);
    p->sws = mp_sws_alloc(vo);
    return 0;
}