#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int last_lit; unsigned int* d_buf; int* l_buf; scalar_t__ pending; scalar_t__ lit_bufsize; int /*<<< orphan*/  last_eob_len; } ;
typedef  TYPE_1__ deflate_state ;
struct TYPE_10__ {int /*<<< orphan*/  Len; } ;
typedef  TYPE_2__ ct_data ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 unsigned int D_CODES ; 
 size_t END_BLOCK ; 
 unsigned int LITERALS ; 
 int /*<<< orphan*/  Tracecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* base_dist ; 
 scalar_t__* base_length ; 
 unsigned int d_code (unsigned int) ; 
 int* extra_dbits ; 
 int* extra_lbits ; 
 int /*<<< orphan*/  isgraph (int) ; 
 unsigned int* length_code ; 
 int /*<<< orphan*/  send_bits (TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  send_code (TYPE_1__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void compress_block(
	deflate_state *s,
	ct_data *ltree, /* literal tree */
	ct_data *dtree  /* distance tree */
)
{
    unsigned dist;      /* distance of matched string */
    int lc;             /* match length or unmatched char (if dist == 0) */
    unsigned lx = 0;    /* running index in l_buf */
    unsigned code;      /* the code to send */
    int extra;          /* number of extra bits to send */

    if (s->last_lit != 0) do {
        dist = s->d_buf[lx];
        lc = s->l_buf[lx++];
        if (dist == 0) {
            send_code(s, lc, ltree); /* send a literal byte */
            Tracecv(isgraph(lc), (stderr," '%c' ", lc));
        } else {
            /* Here, lc is the match length - MIN_MATCH */
            code = length_code[lc];
            send_code(s, code+LITERALS+1, ltree); /* send the length code */
            extra = extra_lbits[code];
            if (extra != 0) {
                lc -= base_length[code];
                send_bits(s, lc, extra);       /* send the extra length bits */
            }
            dist--; /* dist is now the match distance - 1 */
            code = d_code(dist);
            Assert (code < D_CODES, "bad d_code");

            send_code(s, code, dtree);       /* send the distance code */
            extra = extra_dbits[code];
            if (extra != 0) {
                dist -= base_dist[code];
                send_bits(s, dist, extra);   /* send the extra distance bits */
            }
        } /* literal or match pair ? */

        /* Check that the overlay between pending_buf and d_buf+l_buf is ok: */
        Assert(s->pending < s->lit_bufsize + 2*lx, "pendingBuf overflow");

    } while (lx < s->last_lit);

    send_code(s, END_BLOCK, ltree);
    s->last_eob_len = ltree[END_BLOCK].Len;
}