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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOGDIR_NAME_SIZE ; 
 unsigned int RIM_CHUNK_SIZE ; 
 char* compute_chunk_start_addr (unsigned int) ; 
 int /*<<< orphan*/  err_msg (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ ** fp ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  logdir ; 
 char* logfilename ; 
 int rim_process_pid ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void start_verification_log(unsigned int tid,
					  unsigned int *addr,
					  unsigned int cur_sweep_id,
					  unsigned int prev_sweep_id)
{
	FILE *f;
	char logfile[30];
	char path[LOGDIR_NAME_SIZE + 30];
	char separator[2] = "/";
	char *chunk_start = compute_chunk_start_addr(tid);
	unsigned int size = RIM_CHUNK_SIZE;

	sprintf(logfile, logfilename, tid);
	strcpy(path, logdir);
	strcat(path, separator);
	strcat(path, logfile);
	f = fopen(path, "w");

	if (!f) {
		err_msg("Unable to create logfile\n");
	}

	fp[tid] = f;

	fprintf(f, "----------------------------------------------------------\n");
	fprintf(f, "PID                = %d\n", rim_process_pid);
	fprintf(f, "Thread id          = %02d\n", tid);
	fprintf(f, "Chunk Start Addr   = 0x%016lx\n", (unsigned long)chunk_start);
	fprintf(f, "Chunk Size         = %d\n", size);
	fprintf(f, "Next Store Addr    = 0x%016lx\n", (unsigned long)addr);
	fprintf(f, "Current sweep-id   = 0x%08x\n", cur_sweep_id);
	fprintf(f, "Previous sweep-id  = 0x%08x\n", prev_sweep_id);
	fprintf(f, "----------------------------------------------------------\n");
}