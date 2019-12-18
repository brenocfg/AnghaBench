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
struct HPDF_MD5Context {int* bits; scalar_t__ buf; int /*<<< orphan*/ * in; } ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int HPDF_UINT32 ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MD5ByteReverse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MD5Transform (scalar_t__,int*) ; 

void
HPDF_MD5Final  (HPDF_BYTE              digest[16],
                struct HPDF_MD5Context *ctx)
{
    HPDF_UINT32 count;
    HPDF_BYTE *p;

    /* Compute number of bytes mod 64 */
    count = (ctx->bits[0] >> 3) & 0x3F;

    /* Set the first char of padding to 0x80.  This is safe since there is
       always at least one byte free */
    p = ctx->in + count;
    *p++ = 0x80;

    /* Bytes of padding needed to make 64 bytes */
    count = 64 - 1 - count;

    /* Pad out to 56 mod 64 */
    if (count < 8) {
        /* Two lots of padding:  Pad the first block to 64 bytes */
        HPDF_MemSet (p, 0, count);
        MD5ByteReverse (ctx->in, 16);
        MD5Transform (ctx->buf, (HPDF_UINT32 *) ctx->in);

        /* Now fill the next block with 56 bytes */
        HPDF_MemSet (ctx->in, 0, 56);
    } else {
        /* Pad block to 56 bytes */
        HPDF_MemSet (p, 0, count - 8);
    }
    MD5ByteReverse (ctx->in, 14);

    /* Append length in bits and transform */
    ((HPDF_UINT32 *) ctx->in)[14] = ctx->bits[0];
    ((HPDF_UINT32 *) ctx->in)[15] = ctx->bits[1];

    MD5Transform (ctx->buf, (HPDF_UINT32 *) ctx->in);
    MD5ByteReverse ((HPDF_BYTE *) ctx->buf, 4);
    HPDF_MemCpy ((HPDF_BYTE *)digest, (HPDF_BYTE *)ctx->buf, 16);
    HPDF_MemSet ((HPDF_BYTE *)ctx, 0, sizeof (ctx));   /* In case it's sensitive */
}