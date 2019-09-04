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
struct priv {int /*<<< orphan*/  alsa; } ;
struct mp_chmap_sel {struct priv* tmp; } ;
struct mp_chmap {int dummy; } ;
struct ao {struct priv* priv; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ snd_pcm_chmap_query_t ;
typedef  int /*<<< orphan*/  aname ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,...) ; 
 scalar_t__ SND_CHMAP_TYPE_VAR ; 
 int ao_chmap_sel_adjust2 (struct ao*,struct mp_chmap_sel*,struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_chmap_equals (struct mp_chmap*,struct mp_chmap*) ; 
 scalar_t__ mp_chmap_from_alsa (struct mp_chmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_chmap_reorder_norm (struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 
 scalar_t__ snd_pcm_chmap_print (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  snd_pcm_chmap_type_name (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_free_chmaps (TYPE_1__**) ; 
 TYPE_1__** snd_pcm_query_chmaps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool query_chmaps(struct ao *ao, struct mp_chmap *chmap)
{
    struct priv *p = ao->priv;
    struct mp_chmap_sel chmap_sel = {.tmp = p};

    snd_pcm_chmap_query_t **maps = snd_pcm_query_chmaps(p->alsa);
    if (!maps) {
        MP_VERBOSE(ao, "snd_pcm_query_chmaps() returned NULL\n");
        return false;
    }

    for (int i = 0; maps[i] != NULL; i++) {
        char aname[128];
        if (snd_pcm_chmap_print(&maps[i]->map, sizeof(aname), aname) <= 0)
            aname[0] = '\0';

        struct mp_chmap entry;
        if (mp_chmap_from_alsa(&entry, &maps[i]->map)) {
            struct mp_chmap reorder = entry;
            mp_chmap_reorder_norm(&reorder);

            MP_DBG(ao, "got ALSA chmap: %s (%s) -> %s", aname,
                   snd_pcm_chmap_type_name(maps[i]->type),
                   mp_chmap_to_str(&entry));
            if (!mp_chmap_equals(&entry, &reorder))
                MP_DBG(ao, " -> %s", mp_chmap_to_str(&reorder));
            MP_DBG(ao, "\n");

            struct mp_chmap final =
                maps[i]->type == SND_CHMAP_TYPE_VAR ? reorder : entry;
            mp_chmap_sel_add_map(&chmap_sel, &final);
        } else {
            MP_VERBOSE(ao, "skipping unknown ALSA channel map: %s\n", aname);
        }
    }

    snd_pcm_free_chmaps(maps);

    return ao_chmap_sel_adjust2(ao, &chmap_sel, chmap, false);
}