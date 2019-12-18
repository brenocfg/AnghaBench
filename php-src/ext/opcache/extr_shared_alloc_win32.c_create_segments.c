#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; scalar_t__ pos; void* p; } ;
typedef  TYPE_1__ zend_shared_segment ;
struct TYPE_5__ {char* mmap_base; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_FILEMAP_NAME ; 
 int /*<<< orphan*/  ACCEL_LOG_FATAL ; 
 int /*<<< orphan*/  ACCEL_LOG_WARNING ; 
 int ALLOC_FAILURE ; 
 int ALLOC_FAIL_MAPPING ; 
 int ALLOC_SUCCESS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMapping (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int FILE_MAP_ALL_ACCESS ; 
 int FILE_MAP_EXECUTE ; 
 int FILE_MAP_READ ; 
 int FILE_MAP_WRITE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int MAX_MAP_RETRIES ; 
 void* MapViewOfFileEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * OpenFileMapping (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_EXECUTE_READWRITE ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int SEC_COMMIT ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  VirtualProtect (void*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 TYPE_3__ ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accel_directives ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  create_name_with_username (int /*<<< orphan*/ ) ; 
 scalar_t__ execute_ex ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,void*) ; 
 char* get_mmap_base_file () ; 
 void* mapping_base ; 
 int /*<<< orphan*/ * memfile ; 
 int sscanf (char*,char*,void**) ; 
 int /*<<< orphan*/  zend_shared_alloc_lock_win32 () ; 
 int zend_shared_alloc_reattach (size_t,char**) ; 
 int /*<<< orphan*/  zend_shared_alloc_unlock_win32 () ; 
 int /*<<< orphan*/  zend_win_error_message (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int create_segments(size_t requested_size, zend_shared_segment ***shared_segments_p, int *shared_segments_count, char **error_in)
{
	int err = 0, ret;
	zend_shared_segment *shared_segment;
	int map_retries = 0;
	void *default_mapping_base_set[] = { 0, 0 };
	/* TODO:
	  improve fixed addresses on x64. It still makes no sense to do it as Windows addresses are virtual per se and can or should be randomized anyway
	  through Address Space Layout Radomization (ASLR). We can still let the OS do its job and be sure that each process gets the same address if
	  desired. Not done yet, @zend refused but did not remember the exact reason, pls add info here if one of you know why :)
	*/
#if defined(_WIN64)
	void *vista_mapping_base_set[] = { (void *) 0x0000100000000000, (void *) 0x0000200000000000, (void *) 0x0000300000000000, (void *) 0x0000700000000000, 0 };
	DWORD size_high = (requested_size >> 32), size_low = (requested_size & 0xffffffff);
#else
	void *vista_mapping_base_set[] = { (void *) 0x20000000, (void *) 0x21000000, (void *) 0x30000000, (void *) 0x31000000, (void *) 0x50000000, 0 };
	DWORD size_high = 0, size_low = requested_size;
#endif
	void **wanted_mapping_base = default_mapping_base_set;

	zend_shared_alloc_lock_win32();
	/* Mapping retries: When Apache2 restarts, the parent process startup routine
	   can be called before the child process is killed. In this case, the map will fail
	   and we have to sleep some time (until the child releases the mapping object) and retry.*/
	do {
		memfile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE|FILE_MAP_EXECUTE, 0, create_name_with_username(ACCEL_FILEMAP_NAME));
		if (memfile == NULL) {
			err = GetLastError();
			break;
		}

		ret =  zend_shared_alloc_reattach(requested_size, error_in);
		if (ret == ALLOC_FAIL_MAPPING) {
			err = GetLastError();
			/* Mapping failed, wait for mapping object to get freed and retry */
			CloseHandle(memfile);
			memfile = NULL;
			if (++map_retries >= MAX_MAP_RETRIES) {
				break;
			}
			zend_shared_alloc_unlock_win32();
			Sleep(1000 * (map_retries + 1));
			zend_shared_alloc_lock_win32();
		} else {
			zend_shared_alloc_unlock_win32();
			return ret;
		}
	} while (1);

	if (map_retries == MAX_MAP_RETRIES) {
		zend_shared_alloc_unlock_win32();
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to open file mapping", err);
		*error_in = "OpenFileMapping";
		return ALLOC_FAILURE;
	}

	/* creating segment here */
	*shared_segments_count = 1;
	*shared_segments_p = (zend_shared_segment **) calloc(1, sizeof(zend_shared_segment)+sizeof(void *));
	if (!*shared_segments_p) {
		err = GetLastError();
		zend_shared_alloc_unlock_win32();
		zend_win_error_message(ACCEL_LOG_FATAL, "calloc() failed", err);
		*error_in = "calloc";
		return ALLOC_FAILURE;
	}
	shared_segment = (zend_shared_segment *)((char *)(*shared_segments_p) + sizeof(void *));
	(*shared_segments_p)[0] = shared_segment;

	memfile	= CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE | SEC_COMMIT, size_high, size_low,
								create_name_with_username(ACCEL_FILEMAP_NAME));
	if (memfile == NULL) {
		err = GetLastError();
		zend_shared_alloc_unlock_win32();
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to create file mapping", err);
		*error_in = "CreateFileMapping";
		return ALLOC_FAILURE;
	}

	/* Starting from windows Vista, heap randomization occurs which might cause our mapping base to
	   be taken (fail to map). So under Vista, we try to map into a hard coded predefined addresses
	   in high memory. */
	if (!ZCG(accel_directives).mmap_base || !*ZCG(accel_directives).mmap_base) {
		wanted_mapping_base = vista_mapping_base_set;
	} else {
		char *s = ZCG(accel_directives).mmap_base;

		/* skip leading 0x, %p assumes hexdeciaml format anyway */
		if (*s == '0' && *(s + 1) == 'x') {
			s += 2;
		}
		if (sscanf(s, "%p", &default_mapping_base_set[0]) != 1) {
			zend_shared_alloc_unlock_win32();
			zend_win_error_message(ACCEL_LOG_FATAL, "Bad mapping address specified in opcache.mmap_base", err);
			return ALLOC_FAILURE;
		}
	}

	do {
		shared_segment->p = mapping_base = MapViewOfFileEx(memfile, FILE_MAP_ALL_ACCESS|FILE_MAP_EXECUTE, 0, 0, 0, *wanted_mapping_base);
		if (*wanted_mapping_base == NULL) { /* Auto address (NULL) is the last option on the array */
			break;
		}
		wanted_mapping_base++;
	} while (!mapping_base);

	if (mapping_base == NULL) {
		err = GetLastError();
		zend_shared_alloc_unlock_win32();
		zend_win_error_message(ACCEL_LOG_FATAL, "Unable to create view for file mapping", err);
		*error_in = "MapViewOfFile";
		return ALLOC_FAILURE;
	} else {
		char *mmap_base_file;
		void *execute_ex_base = (void *)execute_ex;
		FILE *fp;
		DWORD old;

		if (!VirtualProtect(mapping_base, requested_size, PAGE_READWRITE, &old)) {
			err = GetLastError();
			zend_win_error_message(ACCEL_LOG_FATAL, "VirtualProtect() failed", err);
			return ALLOC_FAILURE;
		}
		mmap_base_file = get_mmap_base_file();
		fp = fopen(mmap_base_file, "w");
		if (!fp) {
			err = GetLastError();
			zend_shared_alloc_unlock_win32();
			zend_win_error_message(ACCEL_LOG_WARNING, mmap_base_file, err);
			zend_win_error_message(ACCEL_LOG_FATAL, "Unable to write base address", err);
			return ALLOC_FAILURE;
		}
		fprintf(fp, "%p\n", mapping_base);
		fprintf(fp, "%p\n", execute_ex_base);
		fclose(fp);
	}

	shared_segment->pos = 0;
	shared_segment->size = requested_size;

	zend_shared_alloc_unlock_win32();

	return ALLOC_SUCCESS;
}