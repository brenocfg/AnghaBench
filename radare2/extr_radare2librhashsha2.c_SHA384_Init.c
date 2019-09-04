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
typedef  TYPE_1__ R_SHA384_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA384_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha384_initial_hash_value ; 

void SHA384_Init(R_SHA384_CTX *context) {
	if (context == (R_SHA384_CTX *) 0) {
		return;
	}
	memcpy (context->state, sha384_initial_hash_value, SHA512_DIGEST_LENGTH);
	memset (context->buffer, 0, SHA384_BLOCK_LENGTH);
	context->bitcount[0] = context->bitcount[1] = 0;
}