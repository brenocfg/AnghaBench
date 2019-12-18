#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* s; int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  PROP_TABLE ;
typedef  TYPE_1__ PROPERTY_STRING ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_IDX ;

/* Variables and functions */
 scalar_t__ lh_PROPERTY_STRING_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_PROPERTY_STRING_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lh_PROPERTY_STRING_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* new_property_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_free (TYPE_1__*) ; 

__attribute__((used)) static OSSL_PROPERTY_IDX ossl_property_string(PROP_TABLE *t,
                                              OSSL_PROPERTY_IDX *pidx,
                                              const char *s)
{
    PROPERTY_STRING p, *ps, *ps_new;

    p.s = s;
    ps = lh_PROPERTY_STRING_retrieve(t, &p);
    if (ps == NULL && pidx != NULL)
        if ((ps_new = new_property_string(s, pidx)) != NULL) {
            lh_PROPERTY_STRING_insert(t, ps_new);
            if (lh_PROPERTY_STRING_error(t)) {
                property_free(ps_new);
                return 0;
            }
            ps = ps_new;
        }
    return ps != NULL ? ps->idx : 0;
}