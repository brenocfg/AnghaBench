#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct MD5Context {int* count; } ;
typedef  int /*<<< orphan*/  PADDING ;

/* Variables and functions */
 int /*<<< orphan*/  __md5_Encode (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  __md5_Update (struct MD5Context*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __md5_Pad(struct MD5Context *context)
{
	unsigned char bits[8];
	unsigned int idx, padLen;
	unsigned char PADDING[64];

	memset(PADDING, 0, sizeof(PADDING));
	PADDING[0] = 0x80;

	/* Save number of bits */
	__md5_Encode(bits, context->count, 8);

	/* Pad out to 56 mod 64. */
	idx = (context->count[0] >> 3) & 0x3f;
	padLen = (idx < 56) ? (56 - idx) : (120 - idx);
	__md5_Update(context, PADDING, padLen);

	/* Append length (before padding) */
	__md5_Update(context, bits, 8);
}