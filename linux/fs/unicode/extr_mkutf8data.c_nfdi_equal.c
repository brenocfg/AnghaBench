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
struct unicode_data {scalar_t__ gen; scalar_t__ ccc; scalar_t__ utf8nfdi; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nfdi_equal(void *l, void *r)
{
	struct unicode_data *left = l;
	struct unicode_data *right = r;

	if (left->gen != right->gen)
		return 0;
	if (left->ccc != right->ccc)
		return 0;
	if (left->utf8nfdi && right->utf8nfdi &&
	    strcmp(left->utf8nfdi, right->utf8nfdi) == 0)
		return 1;
	if (left->utf8nfdi || right->utf8nfdi)
		return 0;
	return 1;
}