#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * queryEnv; } ;
struct TYPE_7__ {int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {TYPE_1__ md; } ;
typedef  TYPE_2__* EphemeralNamedRelation ;

/* Variables and functions */
 int SPI_ERROR_ARGUMENT ; 
 int SPI_ERROR_REL_DUPLICATE ; 
 int SPI_OK_REL_REGISTER ; 
 int _SPI_begin_call (int) ; 
 TYPE_5__* _SPI_current ; 
 int /*<<< orphan*/  _SPI_end_call (int) ; 
 TYPE_2__* _SPI_find_ENR_by_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_queryEnv () ; 
 int /*<<< orphan*/  register_ENR (int /*<<< orphan*/ *,TYPE_2__*) ; 

int
SPI_register_relation(EphemeralNamedRelation enr)
{
	EphemeralNamedRelation match;
	int			res;

	if (enr == NULL || enr->md.name == NULL)
		return SPI_ERROR_ARGUMENT;

	res = _SPI_begin_call(false);	/* keep current memory context */
	if (res < 0)
		return res;

	match = _SPI_find_ENR_by_name(enr->md.name);
	if (match)
		res = SPI_ERROR_REL_DUPLICATE;
	else
	{
		if (_SPI_current->queryEnv == NULL)
			_SPI_current->queryEnv = create_queryEnv();

		register_ENR(_SPI_current->queryEnv, enr);
		res = SPI_OK_REL_REGISTER;
	}

	_SPI_end_call(false);

	return res;
}