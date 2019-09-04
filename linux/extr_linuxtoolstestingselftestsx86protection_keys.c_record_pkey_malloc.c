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
struct pkey_malloc_record {long size; int prot; void* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf2 (char*,size_t) ; 
 int /*<<< orphan*/  dprintf3 (char*,int,struct pkey_malloc_record*,void*,long) ; 
 int /*<<< orphan*/  memset (struct pkey_malloc_record*,int /*<<< orphan*/ ,int) ; 
 long nr_pkey_malloc_records ; 
 int /*<<< orphan*/  pkey_assert (int /*<<< orphan*/ ) ; 
 struct pkey_malloc_record* pkey_last_malloc_record ; 
 struct pkey_malloc_record* pkey_malloc_records ; 
 struct pkey_malloc_record* realloc (struct pkey_malloc_record*,size_t) ; 

void record_pkey_malloc(void *ptr, long size, int prot)
{
	long i;
	struct pkey_malloc_record *rec = NULL;

	for (i = 0; i < nr_pkey_malloc_records; i++) {
		rec = &pkey_malloc_records[i];
		/* find a free record */
		if (rec)
			break;
	}
	if (!rec) {
		/* every record is full */
		size_t old_nr_records = nr_pkey_malloc_records;
		size_t new_nr_records = (nr_pkey_malloc_records * 2 + 1);
		size_t new_size = new_nr_records * sizeof(struct pkey_malloc_record);
		dprintf2("new_nr_records: %zd\n", new_nr_records);
		dprintf2("new_size: %zd\n", new_size);
		pkey_malloc_records = realloc(pkey_malloc_records, new_size);
		pkey_assert(pkey_malloc_records != NULL);
		rec = &pkey_malloc_records[nr_pkey_malloc_records];
		/*
		 * realloc() does not initialize memory, so zero it from
		 * the first new record all the way to the end.
		 */
		for (i = 0; i < new_nr_records - old_nr_records; i++)
			memset(rec + i, 0, sizeof(*rec));
	}
	dprintf3("filling malloc record[%d/%p]: {%p, %ld}\n",
		(int)(rec - pkey_malloc_records), rec, ptr, size);
	rec->ptr = ptr;
	rec->size = size;
	rec->prot = prot;
	pkey_last_malloc_record = rec;
	nr_pkey_malloc_records++;
}