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
struct evsel {scalar_t__ db_id; } ;
struct db_export {int (* export_evsel ) (struct db_export*,struct evsel*) ;scalar_t__ evsel_last_db_id; } ;

/* Variables and functions */
 int stub1 (struct db_export*,struct evsel*) ; 

int db_export__evsel(struct db_export *dbe, struct evsel *evsel)
{
	if (evsel->db_id)
		return 0;

	evsel->db_id = ++dbe->evsel_last_db_id;

	if (dbe->export_evsel)
		return dbe->export_evsel(dbe, evsel);

	return 0;
}