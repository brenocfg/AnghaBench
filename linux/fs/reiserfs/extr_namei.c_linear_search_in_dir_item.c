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
struct reiserfs_dir_entry {int de_entry_num; int de_item_num; int /*<<< orphan*/  de_ih; scalar_t__ de_gen_number_bit_string; int /*<<< orphan*/  de_bh; struct reiserfs_de_head* de_deh; } ;
struct reiserfs_de_head {int dummy; } ;
struct cpu_key {int dummy; } ;

/* Variables and functions */
 struct reiserfs_de_head* B_I_DEH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_GENERATION_NUMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_HASH_VALUE (int /*<<< orphan*/ ) ; 
 int GOTO_PREVIOUS_ITEM ; 
 int NAME_NOT_FOUND ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  cpu_key_k_offset (struct cpu_key*) ; 
 int /*<<< orphan*/  deh_offset (struct reiserfs_de_head*) ; 
 int ih_entry_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_ih_k_offset (int /*<<< orphan*/ ) ; 
 int reiserfs_match (struct reiserfs_dir_entry*,char const*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_de_name_and_namelen (struct reiserfs_dir_entry*) ; 
 int /*<<< orphan*/  set_de_object_key (struct reiserfs_dir_entry*) ; 
 int /*<<< orphan*/  store_de_entry_key (struct reiserfs_dir_entry*) ; 

__attribute__((used)) static int linear_search_in_dir_item(struct cpu_key *key,
				     struct reiserfs_dir_entry *de,
				     const char *name, int namelen)
{
	struct reiserfs_de_head *deh = de->de_deh;
	int retval;
	int i;

	i = de->de_entry_num;

	if (i == ih_entry_count(de->de_ih) ||
	    GET_HASH_VALUE(deh_offset(deh + i)) !=
	    GET_HASH_VALUE(cpu_key_k_offset(key))) {
		i--;
	}

	RFALSE(de->de_deh != B_I_DEH(de->de_bh, de->de_ih),
	       "vs-7010: array of entry headers not found");

	deh += i;

	for (; i >= 0; i--, deh--) {
		/* hash value does not match, no need to check whole name */
		if (GET_HASH_VALUE(deh_offset(deh)) !=
		    GET_HASH_VALUE(cpu_key_k_offset(key))) {
			return NAME_NOT_FOUND;
		}

		/* mark that this generation number is used */
		if (de->de_gen_number_bit_string)
			set_bit(GET_GENERATION_NUMBER(deh_offset(deh)),
				de->de_gen_number_bit_string);

		/* calculate pointer to name and namelen */
		de->de_entry_num = i;
		set_de_name_and_namelen(de);

		/*
		 * de's de_name, de_namelen, de_recordlen are set.
		 * Fill the rest.
		 */
		if ((retval =
		     reiserfs_match(de, name, namelen)) != NAME_NOT_FOUND) {

			/* key of pointed object */
			set_de_object_key(de);

			store_de_entry_key(de);

			/* retval can be NAME_FOUND or NAME_FOUND_INVISIBLE */
			return retval;
		}
	}

	if (GET_GENERATION_NUMBER(le_ih_k_offset(de->de_ih)) == 0)
		/*
		 * we have reached left most entry in the node. In common we
		 * have to go to the left neighbor, but if generation counter
		 * is 0 already, we know for sure, that there is no name with
		 * the same hash value
		 */
		/*
		 * FIXME: this work correctly only because hash value can not
		 *  be 0. Btw, in case of Yura's hash it is probably possible,
		 * so, this is a bug
		 */
		return NAME_NOT_FOUND;

	RFALSE(de->de_item_num,
	       "vs-7015: two diritems of the same directory in one node?");

	return GOTO_PREVIOUS_ITEM;
}