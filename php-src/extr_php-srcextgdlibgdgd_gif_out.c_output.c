#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long code_int ;
struct TYPE_5__ {size_t cur_bits; long cur_accum; scalar_t__ n_bits; scalar_t__ free_ent; scalar_t__ maxcode; scalar_t__ g_init_bits; long EOFCode; scalar_t__ clear_flg; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 size_t CUR_BITS_FINISHED ; 
 void* MAXCODE (scalar_t__) ; 
 int /*<<< orphan*/  char_out (unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  flush_char (TYPE_1__*) ; 
 long* masks ; 
 scalar_t__ maxbits ; 
 scalar_t__ maxmaxcode ; 

__attribute__((used)) static void
output(code_int code, GifCtx *ctx)
{
	if (ctx->cur_bits == CUR_BITS_FINISHED) {
		return;
	}

    ctx->cur_accum &= masks[ ctx->cur_bits ];

    if( ctx->cur_bits > 0 )
        ctx->cur_accum |= ((long)code << ctx->cur_bits);
    else
        ctx->cur_accum = code;

    ctx->cur_bits += ctx->n_bits;

    while( ctx->cur_bits >= 8 ) {
        char_out( (unsigned int)(ctx->cur_accum & 0xff), ctx );
        ctx->cur_accum >>= 8;
        ctx->cur_bits -= 8;
    }

    /*
     * If the next entry is going to be too big for the code size,
     * then increase it, if possible.
     */
   if ( ctx->free_ent > ctx->maxcode || ctx->clear_flg ) {

            if( ctx->clear_flg ) {

                ctx->maxcode = MAXCODE (ctx->n_bits = ctx->g_init_bits);
                ctx->clear_flg = 0;

            } else {

                ++(ctx->n_bits);
                if ( ctx->n_bits == maxbits )
                    ctx->maxcode = maxmaxcode;
                else
                    ctx->maxcode = MAXCODE(ctx->n_bits);
            }
        }

    if( code == ctx->EOFCode ) {
        /*
         * At EOF, write the rest of the buffer.
         */
        while( ctx->cur_bits > 0 ) {
                char_out( (unsigned int)(ctx->cur_accum & 0xff), ctx);
                ctx->cur_accum >>= 8;
                ctx->cur_bits -= 8;
        }

		/* Flag that it's done to prevent re-entry. */
		ctx->cur_bits = CUR_BITS_FINISHED;

        flush_char(ctx);
    }
}