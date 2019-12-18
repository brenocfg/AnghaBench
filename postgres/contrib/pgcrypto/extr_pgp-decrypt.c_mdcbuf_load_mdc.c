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
typedef  int /*<<< orphan*/  uint8 ;
struct MDCBufData {scalar_t__ mdc_avail; scalar_t__ mdc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mdcbuf_load_mdc(struct MDCBufData *st, uint8 *src, int len)
{
	memmove(st->mdc_buf + st->mdc_avail, src, len);
	st->mdc_avail += len;
}