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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetDatabaseEncodingName () ; 
 scalar_t__ PrepareClientEncoding (size_t) ; 
 scalar_t__ SetClientEncoding (size_t) ; 
 int backend_startup_complete ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t pending_client_encoding ; 
 TYPE_1__* pg_enc2name_tbl ; 

void
InitializeClientEncoding(void)
{
	Assert(!backend_startup_complete);
	backend_startup_complete = true;

	if (PrepareClientEncoding(pending_client_encoding) < 0 ||
		SetClientEncoding(pending_client_encoding) < 0)
	{
		/*
		 * Oops, the requested conversion is not available. We couldn't fail
		 * before, but we can now.
		 */
		ereport(FATAL,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("conversion between %s and %s is not supported",
						pg_enc2name_tbl[pending_client_encoding].name,
						GetDatabaseEncodingName())));
	}
}