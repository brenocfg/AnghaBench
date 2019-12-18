#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  domain_info; int /*<<< orphan*/  base_typmod; int /*<<< orphan*/  base_typid; int /*<<< orphan*/  base_io; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  JsValue ;
typedef  TYPE_1__ DomainIOData ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_check (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ populate_record_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static Datum
populate_domain(DomainIOData *io,
				Oid typid,
				const char *colname,
				MemoryContext mcxt,
				JsValue *jsv,
				bool isnull)
{
	Datum		res;

	if (isnull)
		res = (Datum) 0;
	else
	{
		res = populate_record_field(io->base_io,
									io->base_typid, io->base_typmod,
									colname, mcxt, PointerGetDatum(NULL),
									jsv, &isnull);
		Assert(!isnull);
	}

	domain_check(res, isnull, typid, &io->domain_info, mcxt);

	return res;
}