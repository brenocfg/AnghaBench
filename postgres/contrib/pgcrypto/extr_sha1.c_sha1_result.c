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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int /*<<< orphan*/ * b8; } ;
struct sha1_ctxt {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sha1_pad (struct sha1_ctxt*) ; 

void
sha1_result(struct sha1_ctxt *ctxt, uint8 *digest0)
{
	uint8	   *digest;

	digest = (uint8 *) digest0;
	sha1_pad(ctxt);
#ifdef WORDS_BIGENDIAN
	memmove(digest, &ctxt->h.b8[0], 20);
#else
	digest[0] = ctxt->h.b8[3];
	digest[1] = ctxt->h.b8[2];
	digest[2] = ctxt->h.b8[1];
	digest[3] = ctxt->h.b8[0];
	digest[4] = ctxt->h.b8[7];
	digest[5] = ctxt->h.b8[6];
	digest[6] = ctxt->h.b8[5];
	digest[7] = ctxt->h.b8[4];
	digest[8] = ctxt->h.b8[11];
	digest[9] = ctxt->h.b8[10];
	digest[10] = ctxt->h.b8[9];
	digest[11] = ctxt->h.b8[8];
	digest[12] = ctxt->h.b8[15];
	digest[13] = ctxt->h.b8[14];
	digest[14] = ctxt->h.b8[13];
	digest[15] = ctxt->h.b8[12];
	digest[16] = ctxt->h.b8[19];
	digest[17] = ctxt->h.b8[18];
	digest[18] = ctxt->h.b8[17];
	digest[19] = ctxt->h.b8[16];
#endif
}