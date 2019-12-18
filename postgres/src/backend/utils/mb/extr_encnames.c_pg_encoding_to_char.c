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
struct TYPE_3__ {int encoding; char const* name; } ;
typedef  TYPE_1__ pg_enc2name ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ PG_VALID_ENCODING (int) ; 
 TYPE_1__* pg_enc2name_tbl ; 

const char *
pg_encoding_to_char(int encoding)
{
	if (PG_VALID_ENCODING(encoding))
	{
		const pg_enc2name *p = &pg_enc2name_tbl[encoding];

		Assert(encoding == p->encoding);
		return p->name;
	}
	return "";
}