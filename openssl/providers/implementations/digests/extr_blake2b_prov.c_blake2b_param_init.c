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
struct TYPE_3__ {int fanout; int depth; int /*<<< orphan*/  personal; int /*<<< orphan*/  salt; int /*<<< orphan*/  reserved; scalar_t__ inner_length; scalar_t__ node_depth; int /*<<< orphan*/  node_offset; int /*<<< orphan*/  leaf_length; scalar_t__ key_length; int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_1__ BLAKE2B_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  BLAKE2B_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void blake2b_param_init(BLAKE2B_PARAM *P)
{
    P->digest_length = BLAKE2B_DIGEST_LENGTH;
    P->key_length    = 0;
    P->fanout        = 1;
    P->depth         = 1;
    store32(P->leaf_length, 0);
    store64(P->node_offset, 0);
    P->node_depth    = 0;
    P->inner_length  = 0;
    memset(P->reserved, 0, sizeof(P->reserved));
    memset(P->salt,     0, sizeof(P->salt));
    memset(P->personal, 0, sizeof(P->personal));
}