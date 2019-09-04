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
struct mp_resample_opts {int /*<<< orphan*/ * avopts; int /*<<< orphan*/  normalize; } ;
struct m_option {int /*<<< orphan*/ * type; } ;
struct af_resample {int /*<<< orphan*/  global_normalize; struct mp_resample_opts opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_option_copy (struct m_option*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  m_option_type_keyvalue_list ; 
 struct mp_resample_opts* mp_get_config_group (struct af_resample*,struct mpv_global*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resample_conf ; 

__attribute__((used)) static void set_defaults(struct mpv_global *global, void *p)
{
    struct af_resample *s = p;

    struct mp_resample_opts *opts = &s->opts;

    struct mp_resample_opts *src_opts =
        mp_get_config_group(s, global, &resample_conf);

    s->global_normalize = src_opts->normalize;

    assert(!opts->avopts); // we don't set a default value, so it must be NULL

    *opts = *src_opts;

    opts->avopts = NULL;
    struct m_option dummy = {.type = &m_option_type_keyvalue_list};
    m_option_copy(&dummy, &opts->avopts, &src_opts->avopts);
}