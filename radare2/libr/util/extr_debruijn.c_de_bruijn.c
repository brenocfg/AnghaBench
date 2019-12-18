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
 void* calloc (int,int) ; 
 int /*<<< orphan*/  de_bruijn_seq (int,int,int,int,int,int*,char*,char const*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char* de_bruijn(const char* charset, int order, int maxlen) {
	if (!charset) {
		return NULL;
	}
	int size = strlen (charset);
	int* prenecklace_a = calloc (size * order, sizeof (int));
	if (!prenecklace_a) {
		return NULL;
	}
	char* sequence = calloc (maxlen + 1, sizeof (char));
	if (!sequence) {
		free (prenecklace_a);
		return NULL;
	}
	de_bruijn_seq (1, 1, order, maxlen, size, prenecklace_a, sequence, charset);
	free (prenecklace_a);
	return sequence;
}