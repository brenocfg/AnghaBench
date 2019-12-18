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
struct item_head {int /*<<< orphan*/  ih_key; } ;
struct buffer_info {struct buffer_head* bi_bh; } ;
struct buffer_head {int b_size; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int FIRST_TO_LAST ; 
 int LAST_TO_FIRST ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int UNFM_P_SIZE ; 
 int get_ih_free_space (struct item_head*) ; 
 int ih_entry_count (struct item_head*) ; 
 scalar_t__ ih_item_body (struct buffer_head*,struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 int le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  le_ih_k_type (struct item_head*) ; 
 int /*<<< orphan*/  leaf_copy_dir_entries (struct buffer_info*,struct buffer_head*,int,int,int,int) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int op_bytes_number (struct item_head*,int) ; 
 int /*<<< orphan*/  op_is_left_mergeable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,struct item_head*) ; 
 int /*<<< orphan*/  sb_from_bi (struct buffer_info*) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head*,int) ; 
 int /*<<< orphan*/  set_le_ih_k_type (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int leaf_copy_boundary_item(struct buffer_info *dest_bi,
				   struct buffer_head *src, int last_first,
				   int bytes_or_entries)
{
	struct buffer_head *dest = dest_bi->bi_bh;
	/* number of items in the source and destination buffers */
	int dest_nr_item, src_nr_item;
	struct item_head *ih;
	struct item_head *dih;

	dest_nr_item = B_NR_ITEMS(dest);

	/*
	 * if ( DEST is empty or first item of SOURCE and last item of
	 * DEST are the items of different objects or of different types )
	 * then there is no need to treat this item differently from the
	 * other items that we copy, so we return
	 */
	if (last_first == FIRST_TO_LAST) {
		ih = item_head(src, 0);
		dih = item_head(dest, dest_nr_item - 1);

		/* there is nothing to merge */
		if (!dest_nr_item
		    || (!op_is_left_mergeable(&ih->ih_key, src->b_size)))
			return 0;

		RFALSE(!ih_item_len(ih),
		       "vs-10010: item can not have empty length");

		if (is_direntry_le_ih(ih)) {
			if (bytes_or_entries == -1)
				/* copy all entries to dest */
				bytes_or_entries = ih_entry_count(ih);
			leaf_copy_dir_entries(dest_bi, src, FIRST_TO_LAST, 0, 0,
					      bytes_or_entries);
			return 1;
		}

		/*
		 * copy part of the body of the first item of SOURCE
		 * to the end of the body of the last item of the DEST
		 * part defined by 'bytes_or_entries'; if bytes_or_entries
		 * == -1 copy whole body; don't create new item header
		 */
		if (bytes_or_entries == -1)
			bytes_or_entries = ih_item_len(ih);

#ifdef CONFIG_REISERFS_CHECK
		else {
			if (bytes_or_entries == ih_item_len(ih)
			    && is_indirect_le_ih(ih))
				if (get_ih_free_space(ih))
					reiserfs_panic(sb_from_bi(dest_bi),
						       "vs-10020",
						       "last unformatted node "
						       "must be filled "
						       "entirely (%h)", ih);
		}
#endif

		/*
		 * merge first item (or its part) of src buffer with the last
		 * item of dest buffer. Both are of the same file
		 */
		leaf_paste_in_buffer(dest_bi,
				     dest_nr_item - 1, ih_item_len(dih),
				     bytes_or_entries, ih_item_body(src, ih), 0);

		if (is_indirect_le_ih(dih)) {
			RFALSE(get_ih_free_space(dih),
			       "vs-10030: merge to left: last unformatted node of non-last indirect item %h must have zerto free space",
			       ih);
			if (bytes_or_entries == ih_item_len(ih))
				set_ih_free_space(dih, get_ih_free_space(ih));
		}

		return 1;
	}

	/* copy boundary item to right (last_first == LAST_TO_FIRST) */

	/*
	 * (DEST is empty or last item of SOURCE and first item of DEST
	 * are the items of different object or of different types)
	 */
	src_nr_item = B_NR_ITEMS(src);
	ih = item_head(src, src_nr_item - 1);
	dih = item_head(dest, 0);

	if (!dest_nr_item || !op_is_left_mergeable(&dih->ih_key, src->b_size))
		return 0;

	if (is_direntry_le_ih(ih)) {
		/*
		 * bytes_or_entries = entries number in last
		 * item body of SOURCE
		 */
		if (bytes_or_entries == -1)
			bytes_or_entries = ih_entry_count(ih);

		leaf_copy_dir_entries(dest_bi, src, LAST_TO_FIRST,
				      src_nr_item - 1,
				      ih_entry_count(ih) - bytes_or_entries,
				      bytes_or_entries);
		return 1;
	}

	/*
	 * copy part of the body of the last item of SOURCE to the
	 * begin of the body of the first item of the DEST; part defined
	 * by 'bytes_or_entries'; if byte_or_entriess == -1 copy whole body;
	 * change first item key of the DEST; don't create new item header
	 */

	RFALSE(is_indirect_le_ih(ih) && get_ih_free_space(ih),
	       "vs-10040: merge to right: last unformatted node of non-last indirect item must be filled entirely (%h)",
	       ih);

	if (bytes_or_entries == -1) {
		/* bytes_or_entries = length of last item body of SOURCE */
		bytes_or_entries = ih_item_len(ih);

		RFALSE(le_ih_k_offset(dih) !=
		       le_ih_k_offset(ih) + op_bytes_number(ih, src->b_size),
		       "vs-10050: items %h and %h do not match", ih, dih);

		/* change first item key of the DEST */
		set_le_ih_k_offset(dih, le_ih_k_offset(ih));

		/* item becomes non-mergeable */
		/* or mergeable if left item was */
		set_le_ih_k_type(dih, le_ih_k_type(ih));
	} else {
		/* merge to right only part of item */
		RFALSE(ih_item_len(ih) <= bytes_or_entries,
		       "vs-10060: no so much bytes %lu (needed %lu)",
		       (unsigned long)ih_item_len(ih),
		       (unsigned long)bytes_or_entries);

		/* change first item key of the DEST */
		if (is_direct_le_ih(dih)) {
			RFALSE(le_ih_k_offset(dih) <=
			       (unsigned long)bytes_or_entries,
			       "vs-10070: dih %h, bytes_or_entries(%d)", dih,
			       bytes_or_entries);
			set_le_ih_k_offset(dih,
					   le_ih_k_offset(dih) -
					   bytes_or_entries);
		} else {
			RFALSE(le_ih_k_offset(dih) <=
			       (bytes_or_entries / UNFM_P_SIZE) * dest->b_size,
			       "vs-10080: dih %h, bytes_or_entries(%d)",
			       dih,
			       (bytes_or_entries / UNFM_P_SIZE) * dest->b_size);
			set_le_ih_k_offset(dih,
					   le_ih_k_offset(dih) -
					   ((bytes_or_entries / UNFM_P_SIZE) *
					    dest->b_size));
		}
	}

	leaf_paste_in_buffer(dest_bi, 0, 0, bytes_or_entries,
			     ih_item_body(src,
				       ih) + ih_item_len(ih) - bytes_or_entries,
			     0);
	return 1;
}