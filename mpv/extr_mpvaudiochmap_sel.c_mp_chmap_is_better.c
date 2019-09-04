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
struct mp_chmap {scalar_t__ num; } ;

/* Variables and functions */
 int mp_chmap_diffn (struct mp_chmap*,struct mp_chmap*) ; 
 int mp_chmap_diffn_r (struct mp_chmap*,struct mp_chmap*) ; 
 scalar_t__ mp_chmap_equals (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_remove_na (struct mp_chmap*) ; 
 int test_preferred_remix (struct mp_chmap*,struct mp_chmap*) ; 

__attribute__((used)) static bool mp_chmap_is_better(struct mp_chmap *req, struct mp_chmap *old,
                               struct mp_chmap *new)
{
    // Initial case
    if (!old->num)
        return true;

    // Exact pick - this also ensures that the best layout is chosen if the
    // layouts are the same, but with different order of channels.
    if (mp_chmap_equals(req, old))
        return false;
    if (mp_chmap_equals(req, new))
        return true;

    // If there's no exact match, strictly do a preferred conversion.
    bool old_pref = test_preferred_remix(req, old);
    bool new_pref = test_preferred_remix(req, new);
    if (old_pref && !new_pref)
        return false;
    if (!old_pref && new_pref)
        return true;

    int old_lost_r = mp_chmap_diffn_r(req, old); // num. channels only in req
    int new_lost_r = mp_chmap_diffn_r(req, new);

    // Imperfect upmix (no real superset) - minimize lost channels
    if (new_lost_r != old_lost_r)
        return new_lost_r < old_lost_r;

    struct mp_chmap old_p = *old, new_p = *new;
    mp_chmap_remove_na(&old_p);
    mp_chmap_remove_na(&new_p);

    // If the situation is equal with replaced speakers, but the replacement is
    // perfect for only one of them, let the better one win. This prefers
    // inexact equivalents over exact supersets.
    bool perfect_r_new = !new_lost_r && new_p.num <= old_p.num;
    bool perfect_r_old = !old_lost_r && old_p.num <= new_p.num;
    if (perfect_r_new != perfect_r_old)
        return perfect_r_new;

    int old_lost = mp_chmap_diffn(req, old);
    int new_lost = mp_chmap_diffn(req, new);
    // If the situation is equal with replaced speakers, pick the better one,
    // even if it means an upmix.
    if (new_lost != old_lost)
        return new_lost < old_lost;

    // Some kind of upmix. If it's perfect, prefer the smaller one. Even if not,
    // both have equal loss, so also prefer the smaller one.
    // Drop padding channels (NA) for the sake of this check, as the number of
    // padding channels isn't really meaningful.
    if (new_p.num != old_p.num)
        return new_p.num < old_p.num;

    // Again, with physical channels (minimizes number of NA channels).
    return new->num < old->num;
}