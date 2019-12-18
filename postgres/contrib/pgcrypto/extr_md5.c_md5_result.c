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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/ * md5_st8; } ;
typedef  TYPE_1__ md5_ctxt ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
md5_result(uint8 *digest, md5_ctxt *ctxt)
{
	/* 4 byte words */
#ifndef WORDS_BIGENDIAN
	memmove(digest, &ctxt->md5_st8[0], 16);
#else
	digest[0] = ctxt->md5_st8[3];
	digest[1] = ctxt->md5_st8[2];
	digest[2] = ctxt->md5_st8[1];
	digest[3] = ctxt->md5_st8[0];
	digest[4] = ctxt->md5_st8[7];
	digest[5] = ctxt->md5_st8[6];
	digest[6] = ctxt->md5_st8[5];
	digest[7] = ctxt->md5_st8[4];
	digest[8] = ctxt->md5_st8[11];
	digest[9] = ctxt->md5_st8[10];
	digest[10] = ctxt->md5_st8[9];
	digest[11] = ctxt->md5_st8[8];
	digest[12] = ctxt->md5_st8[15];
	digest[13] = ctxt->md5_st8[14];
	digest[14] = ctxt->md5_st8[13];
	digest[15] = ctxt->md5_st8[12];
#endif
}