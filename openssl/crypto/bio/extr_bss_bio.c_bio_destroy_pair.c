#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bio_bio_st {scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/ * buf; TYPE_1__* peer; } ;
struct TYPE_3__ {scalar_t__ init; struct bio_bio_st* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void bio_destroy_pair(BIO *bio)
{
    struct bio_bio_st *b = bio->ptr;

    if (b != NULL) {
        BIO *peer_bio = b->peer;

        if (peer_bio != NULL) {
            struct bio_bio_st *peer_b = peer_bio->ptr;

            assert(peer_b != NULL);
            assert(peer_b->peer == bio);

            peer_b->peer = NULL;
            peer_bio->init = 0;
            assert(peer_b->buf != NULL);
            peer_b->len = 0;
            peer_b->offset = 0;

            b->peer = NULL;
            bio->init = 0;
            assert(b->buf != NULL);
            b->len = 0;
            b->offset = 0;
        }
    }
}