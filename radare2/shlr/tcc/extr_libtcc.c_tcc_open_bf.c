#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int line_num; int fd; struct TYPE_7__* prev; int /*<<< orphan*/  ifdef_stack_ptr; scalar_t__ ifndef_macro; int /*<<< orphan*/  filename; int /*<<< orphan*/ * buf_end; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * buf_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifdef_stack_ptr; } ;
typedef  TYPE_1__ TCCState ;
typedef  TYPE_2__ BufferedFile ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EOB ; 
 int IO_BUF_SIZE ; 
 TYPE_2__* file ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  normalize_slashes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrcpy (int /*<<< orphan*/ ,int,char const*) ; 

void tcc_open_bf(TCCState *s1, const char *filename, int initlen)
{
	BufferedFile *bf;
	int buflen = initlen? initlen: IO_BUF_SIZE;

	bf = malloc (sizeof(BufferedFile) + buflen);
	bf->buf_ptr = bf->buffer;
	bf->buf_end = bf->buffer + initlen;
	bf->buf_end[0] = CH_EOB;/* put eob symbol */
	pstrcpy (bf->filename, sizeof(bf->filename), filename);
#ifdef __WINDOWS__
	normalize_slashes (bf->filename);
#endif
	bf->line_num = 1;
	bf->ifndef_macro = 0;
	bf->ifdef_stack_ptr = s1->ifdef_stack_ptr;
	bf->fd = -1;
	bf->prev = file;
	file = bf;
}