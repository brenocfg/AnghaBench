#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct bio_bio_st {size_t size; int closed; scalar_t__ len; TYPE_1__* peer; int /*<<< orphan*/ * buf; int /*<<< orphan*/  offset; scalar_t__ request; } ;
struct TYPE_12__ {long shutdown; struct bio_bio_st* ptr; } ;
struct TYPE_11__ {struct bio_bio_st* ptr; } ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 147 
#define  BIO_CTRL_EOF 146 
#define  BIO_CTRL_FLUSH 145 
#define  BIO_CTRL_GET_CLOSE 144 
#define  BIO_CTRL_PENDING 143 
#define  BIO_CTRL_RESET 142 
#define  BIO_CTRL_SET_CLOSE 141 
#define  BIO_CTRL_WPENDING 140 
#define  BIO_C_DESTROY_BIO_PAIR 139 
#define  BIO_C_GET_READ_REQUEST 138 
#define  BIO_C_GET_WRITE_BUF_SIZE 137 
#define  BIO_C_GET_WRITE_GUARANTEE 136 
#define  BIO_C_MAKE_BIO_PAIR 135 
#define  BIO_C_NREAD 134 
#define  BIO_C_NREAD0 133 
#define  BIO_C_NWRITE 132 
#define  BIO_C_NWRITE0 131 
#define  BIO_C_RESET_READ_REQUEST 130 
#define  BIO_C_SET_WRITE_BUF_SIZE 129 
#define  BIO_C_SHUTDOWN_WR 128 
 int /*<<< orphan*/  BIO_F_BIO_CTRL ; 
 int /*<<< orphan*/  BIO_R_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  BIO_R_IN_USE ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_destroy_pair (TYPE_2__*) ; 
 int /*<<< orphan*/  bio_make_pair (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ bio_nread (TYPE_2__*,void*,size_t) ; 
 scalar_t__ bio_nread0 (TYPE_2__*,void*) ; 
 scalar_t__ bio_nwrite (TYPE_2__*,void*,size_t) ; 
 scalar_t__ bio_nwrite0 (TYPE_2__*,void*) ; 

__attribute__((used)) static long bio_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret;
    struct bio_bio_st *b = bio->ptr;

    assert(b != NULL);

    switch (cmd) {
        /* specific CTRL codes */

    case BIO_C_SET_WRITE_BUF_SIZE:
        if (b->peer) {
            BIOerr(BIO_F_BIO_CTRL, BIO_R_IN_USE);
            ret = 0;
        } else if (num == 0) {
            BIOerr(BIO_F_BIO_CTRL, BIO_R_INVALID_ARGUMENT);
            ret = 0;
        } else {
            size_t new_size = num;

            if (b->size != new_size) {
                OPENSSL_free(b->buf);
                b->buf = NULL;
                b->size = new_size;
            }
            ret = 1;
        }
        break;

    case BIO_C_GET_WRITE_BUF_SIZE:
        ret = (long)b->size;
        break;

    case BIO_C_MAKE_BIO_PAIR:
        {
            BIO *other_bio = ptr;

            if (bio_make_pair(bio, other_bio))
                ret = 1;
            else
                ret = 0;
        }
        break;

    case BIO_C_DESTROY_BIO_PAIR:
        /*
         * Affects both BIOs in the pair -- call just once! Or let
         * BIO_free(bio1); BIO_free(bio2); do the job.
         */
        bio_destroy_pair(bio);
        ret = 1;
        break;

    case BIO_C_GET_WRITE_GUARANTEE:
        /*
         * How many bytes can the caller feed to the next write without
         * having to keep any?
         */
        if (b->peer == NULL || b->closed)
            ret = 0;
        else
            ret = (long)b->size - b->len;
        break;

    case BIO_C_GET_READ_REQUEST:
        /*
         * If the peer unsuccessfully tried to read, how many bytes were
         * requested? (As with BIO_CTRL_PENDING, that number can usually be
         * treated as boolean.)
         */
        ret = (long)b->request;
        break;

    case BIO_C_RESET_READ_REQUEST:
        /*
         * Reset request.  (Can be useful after read attempts at the other
         * side that are meant to be non-blocking, e.g. when probing SSL_read
         * to see if any data is available.)
         */
        b->request = 0;
        ret = 1;
        break;

    case BIO_C_SHUTDOWN_WR:
        /* similar to shutdown(..., SHUT_WR) */
        b->closed = 1;
        ret = 1;
        break;

    case BIO_C_NREAD0:
        /* prepare for non-copying read */
        ret = (long)bio_nread0(bio, ptr);
        break;

    case BIO_C_NREAD:
        /* non-copying read */
        ret = (long)bio_nread(bio, ptr, (size_t)num);
        break;

    case BIO_C_NWRITE0:
        /* prepare for non-copying write */
        ret = (long)bio_nwrite0(bio, ptr);
        break;

    case BIO_C_NWRITE:
        /* non-copying write */
        ret = (long)bio_nwrite(bio, ptr, (size_t)num);
        break;

        /* standard CTRL codes follow */

    case BIO_CTRL_RESET:
        if (b->buf != NULL) {
            b->len = 0;
            b->offset = 0;
        }
        ret = 0;
        break;

    case BIO_CTRL_GET_CLOSE:
        ret = bio->shutdown;
        break;

    case BIO_CTRL_SET_CLOSE:
        bio->shutdown = (int)num;
        ret = 1;
        break;

    case BIO_CTRL_PENDING:
        if (b->peer != NULL) {
            struct bio_bio_st *peer_b = b->peer->ptr;

            ret = (long)peer_b->len;
        } else
            ret = 0;
        break;

    case BIO_CTRL_WPENDING:
        if (b->buf != NULL)
            ret = (long)b->len;
        else
            ret = 0;
        break;

    case BIO_CTRL_DUP:
        /* See BIO_dup_chain for circumstances we have to expect. */
        {
            BIO *other_bio = ptr;
            struct bio_bio_st *other_b;

            assert(other_bio != NULL);
            other_b = other_bio->ptr;
            assert(other_b != NULL);

            assert(other_b->buf == NULL); /* other_bio is always fresh */

            other_b->size = b->size;
        }

        ret = 1;
        break;

    case BIO_CTRL_FLUSH:
        ret = 1;
        break;

    case BIO_CTRL_EOF:
        if (b->peer != NULL) {
            struct bio_bio_st *peer_b = b->peer->ptr;

            if (peer_b->len == 0 && peer_b->closed)
                ret = 1;
            else
                ret = 0;
        } else {
            ret = 1;
        }
        break;

    default:
        ret = 0;
    }
    return ret;
}