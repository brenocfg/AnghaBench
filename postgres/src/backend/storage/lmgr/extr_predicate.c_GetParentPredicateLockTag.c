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
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GET_PREDICATELOCKTARGETTAG_DB (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  GET_PREDICATELOCKTARGETTAG_PAGE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  GET_PREDICATELOCKTARGETTAG_RELATION (int /*<<< orphan*/  const) ; 
 int GET_PREDICATELOCKTARGETTAG_TYPE (int /*<<< orphan*/  const) ; 
#define  PREDLOCKTAG_PAGE 130 
#define  PREDLOCKTAG_RELATION 129 
#define  PREDLOCKTAG_TUPLE 128 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_PAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_RELATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
GetParentPredicateLockTag(const PREDICATELOCKTARGETTAG *tag,
						  PREDICATELOCKTARGETTAG *parent)
{
	switch (GET_PREDICATELOCKTARGETTAG_TYPE(*tag))
	{
		case PREDLOCKTAG_RELATION:
			/* relation locks have no parent lock */
			return false;

		case PREDLOCKTAG_PAGE:
			/* parent lock is relation lock */
			SET_PREDICATELOCKTARGETTAG_RELATION(*parent,
												GET_PREDICATELOCKTARGETTAG_DB(*tag),
												GET_PREDICATELOCKTARGETTAG_RELATION(*tag));

			return true;

		case PREDLOCKTAG_TUPLE:
			/* parent lock is page lock */
			SET_PREDICATELOCKTARGETTAG_PAGE(*parent,
											GET_PREDICATELOCKTARGETTAG_DB(*tag),
											GET_PREDICATELOCKTARGETTAG_RELATION(*tag),
											GET_PREDICATELOCKTARGETTAG_PAGE(*tag));
			return true;
	}

	/* not reachable */
	Assert(false);
	return false;
}