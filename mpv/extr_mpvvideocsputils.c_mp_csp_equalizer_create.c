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
struct mpv_global {int dummy; } ;
struct mp_csp_equalizer_state {int dummy; } ;
struct m_config_cache {int dummy; } ;

/* Variables and functions */
 struct m_config_cache* m_config_cache_alloc (void*,struct mpv_global*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_csp_equalizer_conf ; 

struct mp_csp_equalizer_state *mp_csp_equalizer_create(void *ta_parent,
                                                    struct mpv_global *global)
{
    struct m_config_cache *c = m_config_cache_alloc(ta_parent, global,
                                                    &mp_csp_equalizer_conf);
    // The terrible, terrible truth.
    return (struct mp_csp_equalizer_state *)c;
}