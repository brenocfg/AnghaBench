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
struct sparsebit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 struct sparsebit* calloc (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

struct sparsebit *sparsebit_alloc(void)
{
	struct sparsebit *s;

	/* Allocate top level structure. */
	s = calloc(1, sizeof(*s));
	if (!s) {
		perror("calloc");
		abort();
	}

	return s;
}