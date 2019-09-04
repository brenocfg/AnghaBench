#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int dummy; } ;
struct playlist {int /*<<< orphan*/  current; int /*<<< orphan*/  first; } ;
struct m_property {int dummy; } ;
struct m_option {int min; int /*<<< orphan*/  max; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {struct playlist* playlist; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_RANGE ; 
 int /*<<< orphan*/  CONF_TYPE_INT ; 
 int M_PROPERTY_ERROR ; 
#define  M_PROPERTY_GET 130 
#define  M_PROPERTY_GET_TYPE 129 
 int M_PROPERTY_NOT_IMPLEMENTED ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_SET 128 
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  mp_set_playlist_entry (TYPE_1__*,struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_entry_count (struct playlist*) ; 
 struct playlist_entry* playlist_entry_from_index (struct playlist*,int) ; 
 int playlist_entry_to_index (struct playlist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_playlist_pos_x(void *ctx, struct m_property *prop,
                                      int action, void *arg, int base)
{
    MPContext *mpctx = ctx;
    struct playlist *pl = mpctx->playlist;
    if (!pl->first)
        return M_PROPERTY_UNAVAILABLE;

    switch (action) {
    case M_PROPERTY_GET: {
        int pos = playlist_entry_to_index(pl, pl->current);
        if (pos < 0)
            return M_PROPERTY_UNAVAILABLE;
        *(int *)arg = pos + base;
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_SET: {
        int pos = *(int *)arg - base;
        struct playlist_entry *e = playlist_entry_from_index(pl, pos);
        if (!e)
            return M_PROPERTY_ERROR;
        mp_set_playlist_entry(mpctx, e);
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_GET_TYPE: {
        struct m_option opt = {
            .type = CONF_TYPE_INT,
            .flags = CONF_RANGE,
            .min = base,
            .max = playlist_entry_count(pl) - 1 + base,
        };
        *(struct m_option *)arg = opt;
        return M_PROPERTY_OK;
    }
    }
    return M_PROPERTY_NOT_IMPLEMENTED;
}