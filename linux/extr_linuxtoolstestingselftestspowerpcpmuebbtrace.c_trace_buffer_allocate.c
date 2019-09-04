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
typedef  int u64 ;
struct trace_buffer {int size; int overflow; int /*<<< orphan*/  data; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 struct trace_buffer* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct trace_buffer* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

struct trace_buffer *trace_buffer_allocate(u64 size)
{
	struct trace_buffer *tb;

	if (size < sizeof(*tb)) {
		fprintf(stderr, "Error: trace buffer too small\n");
		return NULL;
	}

	tb = mmap(NULL, size, PROT_READ | PROT_WRITE,
		  MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (tb == MAP_FAILED) {
		perror("mmap");
		return NULL;
	}

	tb->size = size;
	tb->tail = tb->data;
	tb->overflow = false;

	return tb;
}