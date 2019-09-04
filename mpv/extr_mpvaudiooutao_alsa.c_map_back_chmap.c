#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/  alsa; } ;
struct mp_chmap {int num; } ;
struct ao {struct priv* priv; } ;
struct TYPE_8__ {int channels; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_1__ snd_pcm_chmap_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pos; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_5__ map; } ;
typedef  TYPE_2__ snd_pcm_chmap_query_t ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 scalar_t__ SND_CHMAP_TYPE_VAR ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ mp_chmap_equals (struct mp_chmap*,struct mp_chmap*) ; 
 scalar_t__ mp_chmap_equals_reordered (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_from_alsa (struct mp_chmap*,TYPE_5__*) ; 
 int /*<<< orphan*/  mp_chmap_get_reorder (int*,struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_is_valid (struct mp_chmap*) ; 
 int /*<<< orphan*/  snd_pcm_free_chmaps (TYPE_2__**) ; 
 TYPE_2__** snd_pcm_query_chmaps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_chmap_t *map_back_chmap(struct ao *ao, struct mp_chmap *chmap)
{
    struct priv *p = ao->priv;
    if (!mp_chmap_is_valid(chmap))
        return NULL;

    snd_pcm_chmap_query_t **maps = snd_pcm_query_chmaps(p->alsa);
    if (!maps)
        return NULL;

    snd_pcm_chmap_t *alsa_chmap = NULL;

    for (int i = 0; maps[i] != NULL; i++) {
        struct mp_chmap entry;
        if (!mp_chmap_from_alsa(&entry, &maps[i]->map))
            continue;

        if (mp_chmap_equals(chmap, &entry) ||
            (mp_chmap_equals_reordered(chmap, &entry) &&
                maps[i]->type == SND_CHMAP_TYPE_VAR))
        {
            alsa_chmap = calloc(1, sizeof(*alsa_chmap) +
                                   sizeof(alsa_chmap->pos[0]) * entry.num);
            if (!alsa_chmap)
                break;
            alsa_chmap->channels = entry.num;

            // Undo if mp_chmap_reorder() was called on the result.
            int reorder[MP_NUM_CHANNELS];
            mp_chmap_get_reorder(reorder, chmap, &entry);
            for (int n = 0; n < entry.num; n++)
                alsa_chmap->pos[n] = maps[i]->map.pos[reorder[n]];
            break;
        }
    }

    snd_pcm_free_chmaps(maps);
    return alsa_chmap;
}