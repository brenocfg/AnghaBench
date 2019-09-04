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
struct mp_decoder_list {int dummy; } ;
struct mp_decoder_entry {int /*<<< orphan*/  desc; int /*<<< orphan*/  decoder; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_add_decoder (struct mp_decoder_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void add_new(struct mp_decoder_list *to, struct mp_decoder_entry *entry,
                    const char *codec)
{
    if (!entry || (codec && strcmp(entry->codec, codec) != 0))
        return;
    mp_add_decoder(to, entry->codec, entry->decoder, entry->desc);
}