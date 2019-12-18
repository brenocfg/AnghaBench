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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  int /*<<< orphan*/  PX_MD ;

/* Variables and functions */
 int MDC_DIGEST_LEN ; 
 int pushf_write (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  px_memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mdc_flush(PushFilter *dst, void *priv)
{
	int			res;
	uint8		pkt[2 + MDC_DIGEST_LEN];
	PX_MD	   *md = priv;

	/*
	 * create mdc pkt
	 */
	pkt[0] = 0xD3;
	pkt[1] = 0x14;				/* MDC_DIGEST_LEN */
	px_md_update(md, pkt, 2);
	px_md_finish(md, pkt + 2);

	res = pushf_write(dst, pkt, 2 + MDC_DIGEST_LEN);
	px_memset(pkt, 0, 2 + MDC_DIGEST_LEN);
	return res;
}