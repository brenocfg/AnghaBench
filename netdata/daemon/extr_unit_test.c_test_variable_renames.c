#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* id; char* name; } ;
struct TYPE_10__ {char* id; char* name; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIM ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/ * buffer_create (int) ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 char* buffer_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  health_api_v1_chart_variables2json (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* rrddim_add (TYPE_1__*,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_name (TYPE_1__*,TYPE_2__*,char*) ; 
 TYPE_1__* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_set_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_variable_renames(void) {
    fprintf(stderr, "Creating chart\n");
    RRDSET *st = rrdset_create_localhost("chart", "ID", NULL, "family", "context", "Unit Testing", "a value", "unittest", NULL, 1, 1, RRDSET_TYPE_LINE);
    fprintf(stderr, "Created chart with id '%s', name '%s'\n", st->id, st->name);

    fprintf(stderr, "Creating dimension DIM1\n");
    RRDDIM *rd1 = rrddim_add(st, "DIM1", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
    fprintf(stderr, "Created dimension with id '%s', name '%s'\n", rd1->id, rd1->name);

    fprintf(stderr, "Creating dimension DIM2\n");
    RRDDIM *rd2 = rrddim_add(st, "DIM2", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
    fprintf(stderr, "Created dimension with id '%s', name '%s'\n", rd2->id, rd2->name);

    fprintf(stderr, "Renaming chart to CHARTNAME1\n");
    rrdset_set_name(st, "CHARTNAME1");
    fprintf(stderr, "Renamed chart with id '%s' to name '%s'\n", st->id, st->name);

    fprintf(stderr, "Renaming chart to CHARTNAME2\n");
    rrdset_set_name(st, "CHARTNAME2");
    fprintf(stderr, "Renamed chart with id '%s' to name '%s'\n", st->id, st->name);

    fprintf(stderr, "Renaming dimension DIM1 to DIM1NAME1\n");
    rrddim_set_name(st, rd1, "DIM1NAME1");
    fprintf(stderr, "Renamed dimension with id '%s' to name '%s'\n", rd1->id, rd1->name);

    fprintf(stderr, "Renaming dimension DIM1 to DIM1NAME2\n");
    rrddim_set_name(st, rd1, "DIM1NAME2");
    fprintf(stderr, "Renamed dimension with id '%s' to name '%s'\n", rd1->id, rd1->name);

    fprintf(stderr, "Renaming dimension DIM2 to DIM2NAME1\n");
    rrddim_set_name(st, rd2, "DIM2NAME1");
    fprintf(stderr, "Renamed dimension with id '%s' to name '%s'\n", rd2->id, rd2->name);

    fprintf(stderr, "Renaming dimension DIM2 to DIM2NAME2\n");
    rrddim_set_name(st, rd2, "DIM2NAME2");
    fprintf(stderr, "Renamed dimension with id '%s' to name '%s'\n", rd2->id, rd2->name);

    BUFFER *buf = buffer_create(1);
    health_api_v1_chart_variables2json(st, buf);
    fprintf(stderr, "%s", buffer_tostring(buf));
    buffer_free(buf);
    return 1;
}