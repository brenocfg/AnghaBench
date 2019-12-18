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
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  lexeme; } ;
typedef  TYPE_1__ LexemeHashKey ;

/* Variables and functions */
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
lexeme_compare(const void *key1, const void *key2)
{
	const LexemeHashKey *d1 = (const LexemeHashKey *) key1;
	const LexemeHashKey *d2 = (const LexemeHashKey *) key2;

	/* First, compare by length */
	if (d1->length > d2->length)
		return 1;
	else if (d1->length < d2->length)
		return -1;
	/* Lengths are equal, do a byte-by-byte comparison */
	return strncmp(d1->lexeme, d2->lexeme, d1->length);
}