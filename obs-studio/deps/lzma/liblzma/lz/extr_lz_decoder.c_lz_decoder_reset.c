#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; int size; int need_reset; scalar_t__ full; scalar_t__ pos; } ;
struct TYPE_5__ {TYPE_1__ dict; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */

__attribute__((used)) static void
lz_decoder_reset(lzma_coder *coder)
{
	coder->dict.pos = 0;
	coder->dict.full = 0;
	coder->dict.buf[coder->dict.size - 1] = '\0';
	coder->dict.need_reset = false;
	return;
}