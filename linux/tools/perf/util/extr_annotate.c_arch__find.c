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
struct arch {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch__key_cmp ; 
 int /*<<< orphan*/  arch__sort () ; 
 int /*<<< orphan*/  architectures ; 
 struct arch* bsearch (char const*,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct arch *arch__find(const char *name)
{
	const int nmemb = ARRAY_SIZE(architectures);
	static bool sorted;

	if (!sorted) {
		arch__sort();
		sorted = true;
	}

	return bsearch(name, architectures, nmemb, sizeof(struct arch), arch__key_cmp);
}