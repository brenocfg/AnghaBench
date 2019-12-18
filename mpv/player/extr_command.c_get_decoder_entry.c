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
struct mp_decoder_list {struct mp_decoder_entry* entries; } ;
struct mp_decoder_entry {int /*<<< orphan*/  desc; int /*<<< orphan*/  decoder; int /*<<< orphan*/  codec; } ;
struct m_sub_property {char* member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUB_PROP_STR (int /*<<< orphan*/ ) ; 
 int m_property_read_sub (struct m_sub_property*,int,void*) ; 

__attribute__((used)) static int get_decoder_entry(int item, int action, void *arg, void *ctx)
{
    struct mp_decoder_list *codecs = ctx;
    struct mp_decoder_entry *c = &codecs->entries[item];

    struct m_sub_property props[] = {
        {"codec",       SUB_PROP_STR(c->codec)},
        {"driver" ,     SUB_PROP_STR(c->decoder)},
        {"description", SUB_PROP_STR(c->desc)},
        {0}
    };

    return m_property_read_sub(props, action, arg);
}