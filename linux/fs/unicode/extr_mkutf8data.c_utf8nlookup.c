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
typedef  int utf8trie_t ;
typedef  int utf8leaf_t ;
struct tree {int index; } ;

/* Variables and functions */
 int BITNUM ; 
 scalar_t__ DECOMPOSE ; 
 scalar_t__ HANGUL ; 
 scalar_t__ LEAF_CCC (int*) ; 
 scalar_t__* LEAF_STR (int*) ; 
 int LEFTNODE ; 
 int NEXTBYTE ; 
 int OFFLEN ; 
 int OFFLEN_SHIFT ; 
 int RIGHTNODE ; 
 int RIGHTPATH ; 
 int TRIENODE ; 
 int* utf8data ; 
 int* utf8hangul (char const*,unsigned char*) ; 

__attribute__((used)) static utf8leaf_t *utf8nlookup(struct tree *tree, unsigned char *hangul,
			       const char *s, size_t len)
{
	utf8trie_t	*trie;
	int		offlen;
	int		offset;
	int		mask;
	int		node;

	if (!tree)
		return NULL;
	if (len == 0)
		return NULL;
	node = 1;
	trie = utf8data + tree->index;
	while (node) {
		offlen = (*trie & OFFLEN) >> OFFLEN_SHIFT;
		if (*trie & NEXTBYTE) {
			if (--len == 0)
				return NULL;
			s++;
		}
		mask = 1 << (*trie & BITNUM);
		if (*s & mask) {
			/* Right leg */
			if (offlen) {
				/* Right node at offset of trie */
				node = (*trie & RIGHTNODE);
				offset = trie[offlen];
				while (--offlen) {
					offset <<= 8;
					offset |= trie[offlen];
				}
				trie += offset;
			} else if (*trie & RIGHTPATH) {
				/* Right node after this node */
				node = (*trie & TRIENODE);
				trie++;
			} else {
				/* No right node. */
				return NULL;
			}
		} else {
			/* Left leg */
			if (offlen) {
				/* Left node after this node. */
				node = (*trie & LEFTNODE);
				trie += offlen + 1;
			} else if (*trie & RIGHTPATH) {
				/* No left node. */
				return NULL;
			} else {
				/* Left node after this node */
				node = (*trie & TRIENODE);
				trie++;
			}
		}
	}
	/*
	 * Hangul decomposition is done algorithmically. These are the
	 * codepoints >= 0xAC00 and <= 0xD7A3. Their UTF-8 encoding is
	 * always 3 bytes long, so s has been advanced twice, and the
	 * start of the sequence is at s-2.
	 */
	if (LEAF_CCC(trie) == DECOMPOSE && LEAF_STR(trie)[0] == HANGUL)
		trie = utf8hangul(s - 2, hangul);
	return trie;
}