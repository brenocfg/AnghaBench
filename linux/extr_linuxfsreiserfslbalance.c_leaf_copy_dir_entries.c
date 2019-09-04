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
struct reiserfs_de_head {int dummy; } ;
struct item_head {int /*<<< orphan*/  ih_key; } ;
struct buffer_info {struct buffer_head* bi_bh; } ;
struct buffer_head {char* b_data; } ;

/* Variables and functions */
 struct reiserfs_de_head* B_I_DEH (struct buffer_head*,struct item_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int DEH_SIZE ; 
 scalar_t__ DOT_OFFSET ; 
 int FIRST_TO_LAST ; 
 int /*<<< orphan*/  KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int LAST_TO_FIRST ; 
 int /*<<< orphan*/  MAX_US_INT ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  TYPE_DIRENTRY ; 
 int /*<<< orphan*/  U32_MAX ; 
 scalar_t__ comp_short_le_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int deh_location (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  deh_offset (struct reiserfs_de_head*) ; 
 int ih_entry_count (struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 int ih_location (struct item_head*) ; 
 int /*<<< orphan*/  is_direntry_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 scalar_t__ le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  leaf_insert_into_buf (struct buffer_info*,int,struct item_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_key (struct buffer_head*,int) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int,int,int,struct reiserfs_de_head*,char*,int) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ih_entry_count (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head*,int) ; 
 int /*<<< orphan*/  put_ih_version (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_key_k_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void leaf_copy_dir_entries(struct buffer_info *dest_bi,
				  struct buffer_head *source, int last_first,
				  int item_num, int from, int copy_count)
{
	struct buffer_head *dest = dest_bi->bi_bh;
	/*
	 * either the number of target item, or if we must create a
	 * new item, the number of the item we will create it next to
	 */
	int item_num_in_dest;

	struct item_head *ih;
	struct reiserfs_de_head *deh;
	int copy_records_len;	/* length of all records in item to be copied */
	char *records;

	ih = item_head(source, item_num);

	RFALSE(!is_direntry_le_ih(ih), "vs-10000: item must be directory item");

	/*
	 * length of all record to be copied and first byte of
	 * the last of them
	 */
	deh = B_I_DEH(source, ih);
	if (copy_count) {
		copy_records_len = (from ? deh_location(&deh[from - 1]) :
				    ih_item_len(ih)) -
		    deh_location(&deh[from + copy_count - 1]);
		records =
		    source->b_data + ih_location(ih) +
		    deh_location(&deh[from + copy_count - 1]);
	} else {
		copy_records_len = 0;
		records = NULL;
	}

	/* when copy last to first, dest buffer can contain 0 items */
	item_num_in_dest =
	    (last_first ==
	     LAST_TO_FIRST) ? ((B_NR_ITEMS(dest)) ? 0 : -1) : (B_NR_ITEMS(dest)
							       - 1);

	/*
	 * if there are no items in dest or the first/last item in
	 * dest is not item of the same directory
	 */
	if ((item_num_in_dest == -1) ||
	    (last_first == FIRST_TO_LAST && le_ih_k_offset(ih) == DOT_OFFSET) ||
	    (last_first == LAST_TO_FIRST
	     && comp_short_le_keys /*COMP_SHORT_KEYS */ (&ih->ih_key,
							 leaf_key(dest,
								  item_num_in_dest))))
	{
		/* create new item in dest */
		struct item_head new_ih;

		/* form item header */
		memcpy(&new_ih.ih_key, &ih->ih_key, KEY_SIZE);
		put_ih_version(&new_ih, KEY_FORMAT_3_5);
		/* calculate item len */
		put_ih_item_len(&new_ih,
				DEH_SIZE * copy_count + copy_records_len);
		put_ih_entry_count(&new_ih, 0);

		if (last_first == LAST_TO_FIRST) {
			/* form key by the following way */
			if (from < ih_entry_count(ih)) {
				set_le_ih_k_offset(&new_ih,
						   deh_offset(&deh[from]));
			} else {
				/*
				 * no entries will be copied to this
				 * item in this function
				 */
				set_le_ih_k_offset(&new_ih, U32_MAX);
				/*
				 * this item is not yet valid, but we
				 * want I_IS_DIRECTORY_ITEM to return 1
				 * for it, so we -1
				 */
			}
			set_le_key_k_type(KEY_FORMAT_3_5, &new_ih.ih_key,
					  TYPE_DIRENTRY);
		}

		/* insert item into dest buffer */
		leaf_insert_into_buf(dest_bi,
				     (last_first ==
				      LAST_TO_FIRST) ? 0 : B_NR_ITEMS(dest),
				     &new_ih, NULL, 0);
	} else {
		/* prepare space for entries */
		leaf_paste_in_buffer(dest_bi,
				     (last_first ==
				      FIRST_TO_LAST) ? (B_NR_ITEMS(dest) -
							1) : 0, MAX_US_INT,
				     DEH_SIZE * copy_count + copy_records_len,
				     records, 0);
	}

	item_num_in_dest =
	    (last_first == FIRST_TO_LAST) ? (B_NR_ITEMS(dest) - 1) : 0;

	leaf_paste_entries(dest_bi, item_num_in_dest,
			   (last_first ==
			    FIRST_TO_LAST) ? ih_entry_count(item_head(dest,
									  item_num_in_dest))
			   : 0, copy_count, deh + from, records,
			   DEH_SIZE * copy_count + copy_records_len);
}