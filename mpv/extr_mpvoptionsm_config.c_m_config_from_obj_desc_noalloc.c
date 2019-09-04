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
struct mp_log {int dummy; } ;
struct m_obj_desc {int /*<<< orphan*/  options; int /*<<< orphan*/  priv_defaults; } ;
struct m_config {int dummy; } ;

/* Variables and functions */
 struct m_config* m_config_new (void*,struct mp_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct m_config *m_config_from_obj_desc_noalloc(void *talloc_ctx,
                                                struct mp_log *log,
                                                struct m_obj_desc *desc)
{
    return m_config_new(talloc_ctx, log, 0, desc->priv_defaults, desc->options);
}