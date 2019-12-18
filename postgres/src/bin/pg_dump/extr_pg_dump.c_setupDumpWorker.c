#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_connection (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setupDumpWorker(Archive *AH)
{
	/*
	 * We want to re-select all the same values the master connection is
	 * using.  We'll have inherited directly-usable values in
	 * AH->sync_snapshot_id and AH->use_role, but we need to translate the
	 * inherited encoding value back to a string to pass to setup_connection.
	 */
	setup_connection(AH,
					 pg_encoding_to_char(AH->encoding),
					 NULL,
					 NULL);
}