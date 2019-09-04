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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {int dummy; } ;
struct krb5_ctx {int enctype; } ;
struct gss_ctx {struct krb5_ctx* internal_ctx_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  ENCTYPE_AES128_CTS_HMAC_SHA1_96 132 
#define  ENCTYPE_AES256_CTS_HMAC_SHA1_96 131 
#define  ENCTYPE_ARCFOUR_HMAC 130 
#define  ENCTYPE_DES3_CBC_RAW 129 
#define  ENCTYPE_DES_CBC_RAW 128 
 int /*<<< orphan*/  gss_unwrap_kerberos_v1 (struct krb5_ctx*,int,struct xdr_buf*) ; 
 int /*<<< orphan*/  gss_unwrap_kerberos_v2 (struct krb5_ctx*,int,struct xdr_buf*) ; 

u32
gss_unwrap_kerberos(struct gss_ctx *gctx, int offset, struct xdr_buf *buf)
{
	struct krb5_ctx	*kctx = gctx->internal_ctx_id;

	switch (kctx->enctype) {
	default:
		BUG();
	case ENCTYPE_DES_CBC_RAW:
	case ENCTYPE_DES3_CBC_RAW:
	case ENCTYPE_ARCFOUR_HMAC:
		return gss_unwrap_kerberos_v1(kctx, offset, buf);
	case ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	case ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		return gss_unwrap_kerberos_v2(kctx, offset, buf);
	}
}