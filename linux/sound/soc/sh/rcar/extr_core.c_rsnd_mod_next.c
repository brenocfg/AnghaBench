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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */
 int RSND_MOD_MAX ; 
 struct rsnd_mod* rsnd_io_to_mod (struct rsnd_dai_stream*,int) ; 

struct rsnd_mod *rsnd_mod_next(int *iterator,
			       struct rsnd_dai_stream *io,
			       enum rsnd_mod_type *array,
			       int array_size)
{
	struct rsnd_mod *mod;
	enum rsnd_mod_type type;
	int max = array ? array_size : RSND_MOD_MAX;

	for (; *iterator < max; (*iterator)++) {
		type = (array) ? array[*iterator] : *iterator;
		mod = rsnd_io_to_mod(io, type);
		if (mod)
			return mod;
	}

	return NULL;
}