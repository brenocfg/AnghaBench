#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct xdr_netobj {scalar_t__ len; scalar_t__ data; } ;
struct krb5_ctx {int flags; TYPE_1__* gk5e; } ;
struct TYPE_2__ {scalar_t__ cksumlength; } ;

/* Variables and functions */
 scalar_t__ GSS_KRB5_TOK_HDR_LEN ; 
 int /*<<< orphan*/  KG2_TOK_MIC ; 
 int KRB5_CTX_FLAG_ACCEPTOR_SUBKEY ; 
 int KRB5_CTX_FLAG_INITIATOR ; 

__attribute__((used)) static void *
setup_token_v2(struct krb5_ctx *ctx, struct xdr_netobj *token)
{
	u16 *ptr;
	void *krb5_hdr;
	u8 *p, flags = 0x00;

	if ((ctx->flags & KRB5_CTX_FLAG_INITIATOR) == 0)
		flags |= 0x01;
	if (ctx->flags & KRB5_CTX_FLAG_ACCEPTOR_SUBKEY)
		flags |= 0x04;

	/* Per rfc 4121, sec 4.2.6.1, there is no header,
	 * just start the token */
	krb5_hdr = ptr = (u16 *)token->data;

	*ptr++ = KG2_TOK_MIC;
	p = (u8 *)ptr;
	*p++ = flags;
	*p++ = 0xff;
	ptr = (u16 *)p;
	*ptr++ = 0xffff;
	*ptr = 0xffff;

	token->len = GSS_KRB5_TOK_HDR_LEN + ctx->gk5e->cksumlength;
	return krb5_hdr;
}