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
struct TYPE_2__ {int /*<<< orphan*/ * queryEnv; } ;
typedef  int /*<<< orphan*/ * EphemeralNamedRelation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* _SPI_current ; 
 int /*<<< orphan*/ * get_ENR (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static EphemeralNamedRelation
_SPI_find_ENR_by_name(const char *name)
{
	/* internal static function; any error is bug in SPI itself */
	Assert(name != NULL);

	/* fast exit if no tuplestores have been added */
	if (_SPI_current->queryEnv == NULL)
		return NULL;

	return get_ENR(_SPI_current->queryEnv, name);
}