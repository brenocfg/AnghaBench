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
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int lexeme_compare (void const*,void const*) ; 

__attribute__((used)) static int
lexeme_match(const void *key1, const void *key2, Size keysize)
{
	/* The keysize parameter is superfluous, the keys store their lengths */
	return lexeme_compare(key1, key2);
}