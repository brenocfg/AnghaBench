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
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_2__ {int bloomLength; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ BloomOptions ;

/* Variables and functions */
 int SIGNWORDBITS ; 
 int /*<<< orphan*/  bl_relopt_kind ; 
 int /*<<< orphan*/  bl_relopt_tab ; 
 scalar_t__ build_reloptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthof (int /*<<< orphan*/ ) ; 

bytea *
bloptions(Datum reloptions, bool validate)
{
	BloomOptions *rdopts;

	/* Parse the user-given reloptions */
	rdopts = (BloomOptions *) build_reloptions(reloptions, validate,
											   bl_relopt_kind,
											   sizeof(BloomOptions),
											   bl_relopt_tab,
											   lengthof(bl_relopt_tab));

	/* Convert signature length from # of bits to # to words, rounding up */
	if (rdopts)
		rdopts->bloomLength = (rdopts->bloomLength + SIGNWORDBITS - 1) / SIGNWORDBITS;

	return (bytea *) rdopts;
}