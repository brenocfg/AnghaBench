#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data4; int /*<<< orphan*/  data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;
struct TYPE_4__ {char* names; int cb_names; TYPE_1__ guid; int /*<<< orphan*/  age; int /*<<< orphan*/  time_date_stamp; int /*<<< orphan*/  version; } ;
typedef  TYPE_2__ SPDBInfoStream ;
typedef  int /*<<< orphan*/  R_STREAM_FILE ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stream_file_read (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void parse_pdb_info_stream(void *parsed_pdb_stream, R_STREAM_FILE *stream) {
	SPDBInfoStream *tmp = (SPDBInfoStream *) parsed_pdb_stream;

	tmp->names = 0;

	stream_file_read (stream, 4, (char *) &tmp->/*data.*/ version);
	stream_file_read (stream, 4, (char *) &tmp->/*data.*/ time_date_stamp);
	stream_file_read (stream, 4, (char *) &tmp->/*data.*/ age);
	stream_file_read (stream, 4, (char *) &tmp->/*data.*/ guid.data1);
	stream_file_read (stream, 2, (char *) &tmp->/*data.*/ guid.data2);
	stream_file_read (stream, 2, (char *) &tmp->/*data.*/ guid.data3);
	stream_file_read (stream, 8, (char *) &tmp->/*data.*/ guid.data4);
	stream_file_read (stream, 4, (char *) &tmp->/*data.*/ cb_names);

	tmp->/*data.*/ names = (char *) calloc (1, tmp->/*data.*/ cb_names);
	stream_file_read (stream, tmp->/*data.*/ cb_names, tmp->/*data.*/ names);
}