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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  ranctx ;
typedef  scalar_t__ const_tree ;

/* Variables and functions */
 unsigned char* ORIG_TYPE_NAME (scalar_t__) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  debug_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  full_shuffle (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  name_hash (unsigned char const*) ; 
 scalar_t__ performance_mode ; 
 int /*<<< orphan*/  performance_shuffle (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raninit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shuffle_seed ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void shuffle(const_tree type, tree *newtree, unsigned long length)
{
	unsigned long i;
	u64 seed[4];
	ranctx prng_state;
	const unsigned char *structname;

	if (length == 0)
		return;

	gcc_assert(TREE_CODE(type) == RECORD_TYPE);

	structname = ORIG_TYPE_NAME(type);

#ifdef __DEBUG_PLUGIN
	fprintf(stderr, "Shuffling struct %s %p\n", (const char *)structname, type);
#ifdef __DEBUG_VERBOSE
	debug_tree((tree)type);
#endif
#endif

	for (i = 0; i < 4; i++) {
		seed[i] = shuffle_seed[i];
		seed[i] ^= name_hash(structname);
	}

	raninit(&prng_state, (u64 *)&seed);

	if (performance_mode)
		performance_shuffle(newtree, length, &prng_state);
	else
		full_shuffle(newtree, length, &prng_state);
}