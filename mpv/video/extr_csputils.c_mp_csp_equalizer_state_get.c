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
struct mp_csp_params {int dummy; } ;
struct mp_csp_equalizer_state {int dummy; } ;
struct mp_csp_equalizer_opts {int dummy; } ;
struct m_config_cache {struct mp_csp_equalizer_opts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_config_cache_update (struct m_config_cache*) ; 
 int /*<<< orphan*/  mp_csp_copy_equalizer_values (struct mp_csp_params*,struct mp_csp_equalizer_opts*) ; 

void mp_csp_equalizer_state_get(struct mp_csp_equalizer_state *state,
                                struct mp_csp_params *params)
{
    struct m_config_cache *c = (struct m_config_cache *)state;
    m_config_cache_update(c);
    struct mp_csp_equalizer_opts *opts = c->opts;
    mp_csp_copy_equalizer_values(params, opts);
}