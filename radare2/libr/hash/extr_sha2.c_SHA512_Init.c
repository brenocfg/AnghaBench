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
struct TYPE_3__ {scalar_t__* bitcount; int /*<<< orphan*/  buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ R_SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_mem_memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha512_initial_hash_value ; 

void SHA512_Init(R_SHA512_CTX *context) {
	if (context == (R_SHA512_CTX *) 0) {
		return;
	}
	memcpy (context->state, sha512_initial_hash_value, SHA512_DIGEST_LENGTH);
	r_mem_memzero (context->buffer, SHA512_BLOCK_LENGTH);
	context->bitcount[0] = context->bitcount[1] = 0;
}