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
typedef  int /*<<< orphan*/  relopt_value ;
typedef  int /*<<< orphan*/  relopt_parse_elt ;
typedef  int /*<<< orphan*/  relopt_kind ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* allocateReloptStruct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fillRelOptions (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parseRelOptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void *
build_reloptions(Datum reloptions, bool validate,
				 relopt_kind kind,
				 Size relopt_struct_size,
				 const relopt_parse_elt *relopt_elems,
				 int num_relopt_elems)
{
	int			numoptions;
	relopt_value *options;
	void	   *rdopts;

	/* parse options specific to given relation option kind */
	options = parseRelOptions(reloptions, validate, kind, &numoptions);
	Assert(numoptions <= num_relopt_elems);

	/* if none set, we're done */
	if (numoptions == 0)
	{
		Assert(options == NULL);
		return NULL;
	}

	/* allocate and fill the structure */
	rdopts = allocateReloptStruct(relopt_struct_size, options, numoptions);
	fillRelOptions(rdopts, relopt_struct_size, options, numoptions,
				   validate, relopt_elems, num_relopt_elems);

	pfree(options);

	return rdopts;
}