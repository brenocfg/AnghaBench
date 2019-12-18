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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int publications_valid ; 
 int /*<<< orphan*/  rel_sync_cache_publication_cb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
publication_invalidation_cb(Datum arg, int cacheid, uint32 hashvalue)
{
	publications_valid = false;

	/*
	 * Also invalidate per-relation cache so that next time the filtering info
	 * is checked it will be updated with the new publication settings.
	 */
	rel_sync_cache_publication_cb(arg, cacheid, hashvalue);
}