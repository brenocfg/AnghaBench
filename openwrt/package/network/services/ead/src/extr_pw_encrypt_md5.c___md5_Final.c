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
struct MD5Context {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __md5_Encode (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __md5_Pad (struct MD5Context*) ; 
 int /*<<< orphan*/  memset (struct MD5Context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __md5_Final(unsigned char digest[16], struct MD5Context *context)
{
	/* Do padding. */
	__md5_Pad(context);

	/* Store state in digest */
	__md5_Encode(digest, context->state, 16);

	/* Zeroize sensitive information. */
	memset(context, 0, sizeof(*context));
}