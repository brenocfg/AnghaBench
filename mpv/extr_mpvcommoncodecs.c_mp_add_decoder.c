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
struct mp_decoder_list {int /*<<< orphan*/  num_entries; int /*<<< orphan*/  entries; } ;
struct mp_decoder_entry {int /*<<< orphan*/  desc; int /*<<< orphan*/  decoder; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_decoder_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_decoder_entry) ; 
 int /*<<< orphan*/  talloc_strdup (struct mp_decoder_list*,char const*) ; 

void mp_add_decoder(struct mp_decoder_list *list, const char *codec,
                    const char *decoder, const char *desc)
{
    struct mp_decoder_entry entry = {
        .codec = talloc_strdup(list, codec),
        .decoder = talloc_strdup(list, decoder),
        .desc = talloc_strdup(list, desc),
    };
    MP_TARRAY_APPEND(list, list->entries, list->num_entries, entry);
}