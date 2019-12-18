#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct special_entry {int size; short feature; scalar_t__ new; scalar_t__ group; scalar_t__ orig; scalar_t__ new_len; scalar_t__ orig_len; int /*<<< orphan*/  jump_or_nop; } ;
struct special_alt {unsigned char orig_len; unsigned char new_len; int skip_orig; int skip_alt; unsigned int new_off; int /*<<< orphan*/  new_sec; scalar_t__ orig_off; int /*<<< orphan*/  orig_sec; scalar_t__ group; int /*<<< orphan*/  jump_or_nop; } ;
struct section {TYPE_1__* data; } ;
struct rela {scalar_t__ addend; TYPE_2__* sym; } ;
struct elf {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  sec; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ d_buf; } ;

/* Variables and functions */
 scalar_t__ STT_SECTION ; 
 int /*<<< orphan*/  WARN_FUNC (char*,struct section*,scalar_t__,...) ; 
 unsigned short X86_FEATURE_POPCNT ; 
 unsigned short X86_FEATURE_SMAP ; 
 struct rela* find_rela_by_dest (struct section*,scalar_t__) ; 
 scalar_t__ uaccess ; 

__attribute__((used)) static int get_alt_entry(struct elf *elf, struct special_entry *entry,
			 struct section *sec, int idx,
			 struct special_alt *alt)
{
	struct rela *orig_rela, *new_rela;
	unsigned long offset;

	offset = idx * entry->size;

	alt->group = entry->group;
	alt->jump_or_nop = entry->jump_or_nop;

	if (alt->group) {
		alt->orig_len = *(unsigned char *)(sec->data->d_buf + offset +
						   entry->orig_len);
		alt->new_len = *(unsigned char *)(sec->data->d_buf + offset +
						  entry->new_len);
	}

	if (entry->feature) {
		unsigned short feature;

		feature = *(unsigned short *)(sec->data->d_buf + offset +
					      entry->feature);

		/*
		 * It has been requested that we don't validate the !POPCNT
		 * feature path which is a "very very small percentage of
		 * machines".
		 */
		if (feature == X86_FEATURE_POPCNT)
			alt->skip_orig = true;

		/*
		 * If UACCESS validation is enabled; force that alternative;
		 * otherwise force it the other way.
		 *
		 * What we want to avoid is having both the original and the
		 * alternative code flow at the same time, in that case we can
		 * find paths that see the STAC but take the NOP instead of
		 * CLAC and the other way around.
		 */
		if (feature == X86_FEATURE_SMAP) {
			if (uaccess)
				alt->skip_orig = true;
			else
				alt->skip_alt = true;
		}
	}

	orig_rela = find_rela_by_dest(sec, offset + entry->orig);
	if (!orig_rela) {
		WARN_FUNC("can't find orig rela", sec, offset + entry->orig);
		return -1;
	}
	if (orig_rela->sym->type != STT_SECTION) {
		WARN_FUNC("don't know how to handle non-section rela symbol %s",
			   sec, offset + entry->orig, orig_rela->sym->name);
		return -1;
	}

	alt->orig_sec = orig_rela->sym->sec;
	alt->orig_off = orig_rela->addend;

	if (!entry->group || alt->new_len) {
		new_rela = find_rela_by_dest(sec, offset + entry->new);
		if (!new_rela) {
			WARN_FUNC("can't find new rela",
				  sec, offset + entry->new);
			return -1;
		}

		alt->new_sec = new_rela->sym->sec;
		alt->new_off = (unsigned int)new_rela->addend;

		/* _ASM_EXTABLE_EX hack */
		if (alt->new_off >= 0x7ffffff0)
			alt->new_off -= 0x7ffffff0;
	}

	return 0;
}