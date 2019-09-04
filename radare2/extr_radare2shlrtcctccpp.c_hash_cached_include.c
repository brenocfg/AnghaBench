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

/* Variables and functions */
 int CACHED_INCLUDES_HASH_SIZE ; 
 unsigned int TOK_HASH_FUNC (unsigned int,unsigned char const) ; 
 unsigned int TOK_HASH_INIT ; 

__attribute__((used)) static inline int hash_cached_include(const char *filename)
{
	const unsigned char *s;
	unsigned int h;

	h = TOK_HASH_INIT;
	s = (const unsigned char *) filename;
	while (*s) {
		h = TOK_HASH_FUNC (h, *s);
		s++;
	}
	h &= (CACHED_INCLUDES_HASH_SIZE - 1);
	return h;
}