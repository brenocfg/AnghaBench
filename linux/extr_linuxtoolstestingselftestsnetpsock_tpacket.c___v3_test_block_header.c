#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int block_status; } ;
struct block_desc {TYPE_1__ h1; } ;

/* Variables and functions */
 int TP_STATUS_USER ; 
 int /*<<< orphan*/  __v3_test_block_seq_num (struct block_desc*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void __v3_test_block_header(struct block_desc *pbd, const int block_num)
{
	if ((pbd->h1.block_status & TP_STATUS_USER) == 0) {
		fprintf(stderr, "\nblock %u: not in TP_STATUS_USER\n", block_num);
		exit(1);
	}

	__v3_test_block_seq_num(pbd);
}