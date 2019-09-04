#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ulg ;
typedef  int /*<<< orphan*/  tree_desc ;
struct TYPE_15__ {scalar_t__ max_code; } ;
struct TYPE_14__ {scalar_t__ max_code; } ;
struct TYPE_16__ {scalar_t__ level; scalar_t__ data_type; int opt_len; int static_len; int compressed_len; int bits_sent; scalar_t__ dyn_dtree; scalar_t__ dyn_ltree; TYPE_2__ d_desc; TYPE_1__ l_desc; int /*<<< orphan*/  last_lit; } ;
typedef  TYPE_3__ deflate_state ;
typedef  int /*<<< orphan*/  ct_data ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 int DYN_TREES ; 
 int STATIC_TREES ; 
 int /*<<< orphan*/  Tracev (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_UNKNOWN ; 
 int /*<<< orphan*/  bi_windup (TYPE_3__*) ; 
 int build_bl_tree (TYPE_3__*) ; 
 int /*<<< orphan*/  build_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compress_block (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_block (TYPE_3__*) ; 
 int /*<<< orphan*/  send_all_trees (TYPE_3__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  send_bits (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  set_data_type (TYPE_3__*) ; 
 scalar_t__ static_dtree ; 
 scalar_t__ static_ltree ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zlib_tr_stored_block (TYPE_3__*,char*,int,int) ; 

ulg zlib_tr_flush_block(
	deflate_state *s,
	char *buf,        /* input block, or NULL if too old */
	ulg stored_len,   /* length of input block */
	int eof           /* true if this is the last block for a file */
)
{
    ulg opt_lenb, static_lenb; /* opt_len and static_len in bytes */
    int max_blindex = 0;  /* index of last bit length code of non zero freq */

    /* Build the Huffman trees unless a stored block is forced */
    if (s->level > 0) {

	 /* Check if the file is ascii or binary */
	if (s->data_type == Z_UNKNOWN) set_data_type(s);

	/* Construct the literal and distance trees */
	build_tree(s, (tree_desc *)(&(s->l_desc)));
	Tracev((stderr, "\nlit data: dyn %ld, stat %ld", s->opt_len,
		s->static_len));

	build_tree(s, (tree_desc *)(&(s->d_desc)));
	Tracev((stderr, "\ndist data: dyn %ld, stat %ld", s->opt_len,
		s->static_len));
	/* At this point, opt_len and static_len are the total bit lengths of
	 * the compressed block data, excluding the tree representations.
	 */

	/* Build the bit length tree for the above two trees, and get the index
	 * in bl_order of the last bit length code to send.
	 */
	max_blindex = build_bl_tree(s);

	/* Determine the best encoding. Compute first the block length in bytes*/
	opt_lenb = (s->opt_len+3+7)>>3;
	static_lenb = (s->static_len+3+7)>>3;

	Tracev((stderr, "\nopt %lu(%lu) stat %lu(%lu) stored %lu lit %u ",
		opt_lenb, s->opt_len, static_lenb, s->static_len, stored_len,
		s->last_lit));

	if (static_lenb <= opt_lenb) opt_lenb = static_lenb;

    } else {
        Assert(buf != (char*)0, "lost buf");
	opt_lenb = static_lenb = stored_len + 5; /* force a stored block */
    }

    /* If compression failed and this is the first and last block,
     * and if the .zip file can be seeked (to rewrite the local header),
     * the whole file is transformed into a stored file:
     */
#ifdef STORED_FILE_OK
#  ifdef FORCE_STORED_FILE
    if (eof && s->compressed_len == 0L) { /* force stored file */
#  else
    if (stored_len <= opt_lenb && eof && s->compressed_len==0L && seekable()) {
#  endif
        /* Since LIT_BUFSIZE <= 2*WSIZE, the input data must be there: */
        if (buf == (char*)0) error ("block vanished");

        copy_block(s, buf, (unsigned)stored_len, 0); /* without header */
        s->compressed_len = stored_len << 3;
        s->method = STORED;
    } else
#endif /* STORED_FILE_OK */

#ifdef FORCE_STORED
    if (buf != (char*)0) { /* force stored block */
#else
    if (stored_len+4 <= opt_lenb && buf != (char*)0) {
                       /* 4: two words for the lengths */
#endif
        /* The test buf != NULL is only necessary if LIT_BUFSIZE > WSIZE.
         * Otherwise we can't have processed more than WSIZE input bytes since
         * the last block flush, because compression would have been
         * successful. If LIT_BUFSIZE <= WSIZE, it is never too late to
         * transform a block into a stored block.
         */
        zlib_tr_stored_block(s, buf, stored_len, eof);

#ifdef FORCE_STATIC
    } else if (static_lenb >= 0) { /* force static trees */
#else
    } else if (static_lenb == opt_lenb) {
#endif
        send_bits(s, (STATIC_TREES<<1)+eof, 3);
        compress_block(s, (ct_data *)static_ltree, (ct_data *)static_dtree);
        s->compressed_len += 3 + s->static_len;
    } else {
        send_bits(s, (DYN_TREES<<1)+eof, 3);
        send_all_trees(s, s->l_desc.max_code+1, s->d_desc.max_code+1,
                       max_blindex+1);
        compress_block(s, (ct_data *)s->dyn_ltree, (ct_data *)s->dyn_dtree);
        s->compressed_len += 3 + s->opt_len;
    }
    Assert (s->compressed_len == s->bits_sent, "bad compressed size");
    init_block(s);

    if (eof) {
        bi_windup(s);
        s->compressed_len += 7;  /* align on byte boundary */
    }
    Tracev((stderr,"\ncomprlen %lu(%lu) ", s->compressed_len>>3,
           s->compressed_len-7*eof));

    return s->compressed_len >> 3;
}