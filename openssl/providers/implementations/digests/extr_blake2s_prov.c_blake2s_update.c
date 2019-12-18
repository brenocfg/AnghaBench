#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int buflen; int /*<<< orphan*/  const* buf; } ;
typedef  TYPE_1__ BLAKE2S_CTX ;

/* Variables and functions */
 size_t BLAKE2S_BLOCKBYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blake2s_compress (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int blake2s_update(BLAKE2S_CTX *c, const void *data, size_t datalen)
{
    const uint8_t *in = data;
    size_t fill;

    /*
     * Intuitively one would expect intermediate buffer, c->buf, to
     * store incomplete blocks. But in this case we are interested to
     * temporarily stash even complete blocks, because last one in the
     * stream has to be treated in special way, and at this point we
     * don't know if last block in *this* call is last one "ever". This
     * is the reason for why |datalen| is compared as >, and not >=.
     */
    fill = sizeof(c->buf) - c->buflen;
    if (datalen > fill) {
        if (c->buflen) {
            memcpy(c->buf + c->buflen, in, fill); /* Fill buffer */
            blake2s_compress(c, c->buf, BLAKE2S_BLOCKBYTES);
            c->buflen = 0;
            in += fill;
            datalen -= fill;
        }
        if (datalen > BLAKE2S_BLOCKBYTES) {
            size_t stashlen = datalen % BLAKE2S_BLOCKBYTES;
            /*
             * If |datalen| is a multiple of the blocksize, stash
             * last complete block, it can be final one...
             */
            stashlen = stashlen ? stashlen : BLAKE2S_BLOCKBYTES;
            datalen -= stashlen;
            blake2s_compress(c, in, datalen);
            in += datalen;
            datalen = stashlen;
        }
    }

    assert(datalen <= BLAKE2S_BLOCKBYTES);

    memcpy(c->buf + c->buflen, in, datalen);
    c->buflen += datalen; /* Be lazy, do not compress */

    return 1;
}