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
struct utf8data {int dummy; } ;
struct utf8cursor {char const* s; size_t len; void* nccc; void* ccc; scalar_t__ slen; int /*<<< orphan*/ * sp; int /*<<< orphan*/ * ss; int /*<<< orphan*/ * p; struct utf8data const* data; } ;

/* Variables and functions */
 void* STOPPER ; 

int utf8ncursor(struct utf8cursor *u8c, const struct utf8data *data,
		const char *s, size_t len)
{
	if (!data)
		return -1;
	if (!s)
		return -1;
	u8c->data = data;
	u8c->s = s;
	u8c->p = NULL;
	u8c->ss = NULL;
	u8c->sp = NULL;
	u8c->len = len;
	u8c->slen = 0;
	u8c->ccc = STOPPER;
	u8c->nccc = STOPPER;
	/* Check we didn't clobber the maximum length. */
	if (u8c->len != len)
		return -1;
	/* The first byte of s may not be an utf8 continuation. */
	if (len > 0 && (*s & 0xC0) == 0x80)
		return -1;
	return 0;
}