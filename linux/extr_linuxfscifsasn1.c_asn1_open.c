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
struct asn1_ctx {unsigned char* begin; unsigned char* end; unsigned char* pointer; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ERR_NOERROR ; 

__attribute__((used)) static void
asn1_open(struct asn1_ctx *ctx, unsigned char *buf, unsigned int len)
{
	ctx->begin = buf;
	ctx->end = buf + len;
	ctx->pointer = buf;
	ctx->error = ASN1_ERR_NOERROR;
}