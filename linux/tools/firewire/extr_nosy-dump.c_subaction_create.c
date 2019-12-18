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
typedef  int /*<<< orphan*/  uint32_t ;
struct subaction {size_t length; int /*<<< orphan*/  packet; int /*<<< orphan*/  ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct subaction* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct subaction *
subaction_create(uint32_t *data, size_t length)
{
	struct subaction *sa;

	/* we put the ack in the subaction struct for easy access. */
	sa = malloc(sizeof *sa - sizeof sa->packet + length);
	if (!sa)
		exit(EXIT_FAILURE);
	sa->ack = data[length / 4 - 1];
	sa->length = length;
	memcpy(&sa->packet, data, length);

	return sa;
}