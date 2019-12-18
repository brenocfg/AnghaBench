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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct TYPE_4__ {int* count; int* state; } ;
typedef  TYPE_1__ R_MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Encode (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  MD5_Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PADDING ; 
 int /*<<< orphan*/  r_mem_memzero (void*,int) ; 

void MD5_Final(ut8 digest[16], R_MD5_CTX *context) {
	ut8 bits[8];

	/* Save number of bits */
	Encode (bits, context->count, 8);

	/* Pad out to 56 mod 64.  */
	ut32 index = (ut32)((context->count[0] >> 3) & 0x3f);
	ut32 padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5_Update (context, PADDING, padLen);

	/* Append length (before padding) */
	MD5_Update (context, bits, 8);

	/* Store state in digest */
	Encode (digest, context->state, 16);

	/* Zeroize sensitive information.  */
	r_mem_memzero ((void*)context, sizeof (*context));
}