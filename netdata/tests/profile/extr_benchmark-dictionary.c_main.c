#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned long long tv_sec; unsigned long long tv_usec; } ;
struct rusage {TYPE_1__ ru_utime; } ;
struct myvalue {int i; } ;
struct TYPE_11__ {TYPE_2__* stats; } ;
struct TYPE_10__ {unsigned long long inserts; unsigned long long deletes; unsigned long long searches; } ;
typedef  TYPE_3__ DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  DICTIONARY_FLAG_WITH_STATISTICS ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 TYPE_3__* dictionary_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_del (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dictionary_destroy (TYPE_3__*) ; 
 struct myvalue* dictionary_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dictionary_set (TYPE_3__*,char*,struct myvalue*,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
	if(argc || argv) {;}

//	DICTIONARY *dict = dictionary_create(DICTIONARY_FLAG_SINGLE_THREADED|DICTIONARY_FLAG_WITH_STATISTICS);
	DICTIONARY *dict = dictionary_create(DICTIONARY_FLAG_WITH_STATISTICS);
	if(!dict) fatal("Cannot create dictionary.");

	struct rusage start, end;
	unsigned long long dt;
	char buf[100 + 1];
	struct myvalue value, *v;
	int i, max = 30000000, max2;

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Inserting %d entries in the dictionary\n", max);
	for(i = 0; i < max; i++) {
		value.i = i;
		snprintf(buf, 100, "%d", i);

		dictionary_set(dict, buf, &value, sizeof(struct myvalue));
	}
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Added %d entries in %llu nanoseconds: %llu inserts per second\n", max, dt, max * 1000000ULL / dt);
	fprintf(stderr, " > Dictionary: %llu inserts, %llu deletes, %llu searches\n\n", dict->stats->inserts, dict->stats->deletes, dict->stats->searches);

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Retrieving %d entries from the dictionary\n", max);
	for(i = 0; i < max; i++) {
		value.i = i;
		snprintf(buf, 100, "%d", i);

		v = dictionary_get(dict, buf);
		if(!v)
			fprintf(stderr, "ERROR: cannot get value %d from the dictionary\n", i);
		else if(v->i != i)
			fprintf(stderr, "ERROR: expected %d but got %d\n", i, v->i);
	}
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Read %d entries in %llu nanoseconds: %llu searches per second\n", max, dt, max * 1000000ULL / dt);
	fprintf(stderr, " > Dictionary: %llu inserts, %llu deletes, %llu searches\n\n", dict->stats->inserts, dict->stats->deletes, dict->stats->searches);

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Resetting %d entries in the dictionary\n", max);
	for(i = 0; i < max; i++) {
		value.i = i;
		snprintf(buf, 100, "%d", i);

		dictionary_set(dict, buf, &value, sizeof(struct myvalue));
	}
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Reset %d entries in %llu nanoseconds: %llu resets per second\n", max, dt, max * 1000000ULL / dt);
	fprintf(stderr, " > Dictionary: %llu inserts, %llu deletes, %llu searches\n\n", dict->stats->inserts, dict->stats->deletes, dict->stats->searches);

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Searching  %d non-existing entries in the dictionary\n", max);
	max2 = max * 2;
	for(i = max; i < max2; i++) {
		value.i = i;
		snprintf(buf, 100, "%d", i);

		v = dictionary_get(dict, buf);
		if(v)
			fprintf(stderr, "ERROR: cannot got non-existing value %d from the dictionary\n", i);
	}
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Searched %d non-existing entries in %llu nanoseconds: %llu not found searches per second\n", max, dt, max * 1000000ULL / dt);
	fprintf(stderr, " > Dictionary: %llu inserts, %llu deletes, %llu searches\n\n", dict->stats->inserts, dict->stats->deletes, dict->stats->searches);

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Deleting %d entries from the dictionary\n", max);
	for(i = 0; i < max; i++) {
		value.i = i;
		snprintf(buf, 100, "%d", i);

		dictionary_del(dict, buf);
	}
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Deleted %d entries in %llu nanoseconds: %llu deletes per second\n", max, dt, max * 1000000ULL / dt);
	fprintf(stderr, " > Dictionary: %llu inserts, %llu deletes, %llu searches\n\n", dict->stats->inserts, dict->stats->deletes, dict->stats->searches);

	// ------------------------------------------------------------------------

	getrusage(RUSAGE_SELF, &start);
	dict->stats->inserts = dict->stats->deletes = dict->stats->searches = 0ULL;
	fprintf(stderr, "Destroying dictionary\n");
	dictionary_destroy(dict);
	getrusage(RUSAGE_SELF, &end);
	dt = (end.ru_utime.tv_sec * 1000000ULL + end.ru_utime.tv_usec) - (start.ru_utime.tv_sec * 1000000ULL + start.ru_utime.tv_usec);
	fprintf(stderr, "Destroyed in %llu nanoseconds\n", dt);

	return 0;
}