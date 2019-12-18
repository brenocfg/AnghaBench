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
struct unicode_data {int /*<<< orphan*/  ccc; scalar_t__ utf8nfdi; int /*<<< orphan*/  code; int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 void* DECOMPOSE ; 
 int /*<<< orphan*/  HANGUL ; 
 scalar_t__ HANGUL_SYLLABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *nfdi_emit(void *l, unsigned char *data)
{
	struct unicode_data *leaf = l;
	unsigned char *s;

	*data++ = leaf->gen;

	if (HANGUL_SYLLABLE(leaf->code)) {
		*data++ = DECOMPOSE;
		*data++ = HANGUL;
	} else if (leaf->utf8nfdi) {
		*data++ = DECOMPOSE;
		s = (unsigned char*)leaf->utf8nfdi;
		while ((*data++ = *s++) != 0)
			;
	} else {
		*data++ = leaf->ccc;
	}
	return data;
}